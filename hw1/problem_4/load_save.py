import os
import struct
import numpy as np


def save_3d_raw(path: str, arr: np.ndarray, *, endian: str = "<") -> None:
    """
    Save a 3D NumPy array to `path` as:
      [ int32 dim0 ][ int32 dim1 ][ int32 dim2 ][ float32 data ... ]
    All integers and floats are written in the specified endianness (default: little-endian).

    Parameters
    ----------
    path : str
        Output file path.
    arr : np.ndarray
        A 3D NumPy array.
    endian : str
        '<' for little-endian, '>' for big-endian (affects both header and data).
    """
    if arr.ndim < 2:
        raise ValueError(f"Expected a 3D array; got ndim={arr.ndim}")

    if arr.ndim == 3:
        d0, d1, d2 = map(int, arr.shape)
    elif arr.ndim == 2:
        d0 = 1
        d1, d2 = map(int, arr.shape)
    else:
        raise Exception("Not sure what to do with nD arrays")

    # Ensure dims fit in signed 32-bit header
    for d in (d0, d1, d2):
        if d < 0 or d > 2 ** 31 - 1:
            raise ValueError(f"Dimension {d} does not fit in int32 header")

    # Make sure the data is contiguous, float32, with the requested byte order
    dt = np.dtype(np.float32).newbyteorder(endian)
    buf = np.ascontiguousarray(arr, dtype=dt)

    with open(path, "wb") as f:
        # 12-byte header: 3 x int32
        f.write(struct.pack(f"{endian}3i", d0, d1, d2))
        # Raw float32 payload in C-order
        f.write(buf.tobytes(order="C"))


def load_3d_raw(path: str, *, endian: str = "<") -> np.ndarray:
    """
    Load a file written by `save_3d_raw`.

    Layout:
      [ int32 dim0 ][ int32 dim1 ][ int32 dim2 ][ float32 data ... ]

    Parameters
    ----------
    path : str
        Input file path.
    endian : str
        '<' for little-endian, '>' for big-endian (must match what was used when saving).

    Returns
    -------
    np.ndarray
        A 3D NumPy array of dtype float32 with the shape from the header.
    """
    header_size = 12  # 3 * int32
    dt = np.dtype(np.float32).newbyteorder(endian)

    with open(path, "rb") as f:
        header = f.read(header_size)
        if len(header) != header_size:
            raise IOError("File too small: missing 12-byte header")

        d0, d1, d2 = struct.unpack(f"{endian}3i", header)
        if d0 < 0 or d1 < 0 or d2 < 0:
            raise ValueError(f"Invalid negative dimensions in header: {(d0, d1, d2)}")

        count = int(d0) * int(d1) * int(d2)
        expected_payload = count * dt.itemsize
        # Optional sanity check against actual file size
        # (helps catch mismatched dtype/endianness or truncated files)
        try:
            file_size = os.fstat(f.fileno()).st_size
            if file_size != header_size + expected_payload:
                # Fallback to reading what's there; then validate count
                pass
        except (AttributeError, OSError):
            # Not all file objects support fileno(); safe to skip.
            pass

        payload = f.read()
        if len(payload) != expected_payload:
            raise IOError(
                f"Unexpected payload size: expected {expected_payload} bytes, "
                f"got {len(payload)} bytes"
            )

    data = np.frombuffer(payload, dtype=dt, count=count)
    return data.reshape((d0, d1, d2), order="C")


def run_load_save():
    np.random.seed(123456789)

    # Create a 3D array (float32)
    arr = np.round((np.random.rand(30, 40, 50) * 1000)).astype(np.float32)

    s = np.sum(arr)
    print(f'sum={s:f}')

    # Save (little-endian)
    save_3d_raw("array_with_dims.bin", arr, endian="<")

    # Load (endianness must match)
    arr2 = load_3d_raw("array_with_dims.bin", endian="<")

    print("Original shape:", arr.shape)
    print("Loaded   shape:", arr2.shape)
    print("Equal (allclose):", np.allclose(arr, arr2))
    print("Dtype:", arr2.dtype)

    assert (np.all(arr.shape == arr2.shape))
    assert (np.allclose(arr, arr2))

    print('Success!!!')


def run_load_save2():
    np.random.seed(123456789)

    # Create a 3D array (float32)
    arr = np.round((np.random.rand(30, 40, 50) * 1000)).astype(np.float32)

    a = load_3d_raw('out.bin', endian='<')
    print(np.allclose(arr / 2.0, a))


if __name__ == "__main__":
    run_load_save()
    run_load_save2()
