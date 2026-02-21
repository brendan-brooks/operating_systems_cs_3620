# Sieve of Eratosthenes (Primes Algorithm)

Implemented the [Sieve of Eratosthenes algorithm](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) to compute the primes 
from 0 to n (inclusive). I chose it because it is quicker than
checking each number manually for all of its factors: O(*n*loglog*n*) vs. O(*n*√*n*)
and showcases the use of `malloc()` and  `free()`. 

### Drawbacks:
Uses O(*n*) space (potentially a huge problem for large *n*),
doesn't optimize for cache locality well (in its multiples-marking), and optimizing further
(beyond stopping the multiples-marking at √*n*) requires making the code
much more complicated and harder to verify.

Looking back, I probably should've just implemented the MVP approach :)

