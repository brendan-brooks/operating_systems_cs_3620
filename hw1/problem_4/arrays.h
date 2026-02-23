
#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t dim1, dim2, dim3;
    float *data;
} Array3D;

// Load a 3D array from a file
Array3D *array3d_load(const char *filename);

// Save a 3D array to a file
void array3d_save(const Array3D *arr, const char *filename);

// Free the memory allocated for a 3D array
void array3d_free(Array3D *arr);

#endif // ARRAYS_H