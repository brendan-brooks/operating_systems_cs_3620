#include <stdio.h>
#include <stdlib.h>     // atoi()
#include <stdbool.h>    // bools

int main(int argc, char* argv[]) {

    if (argc != 2) {                // Check number of command line arguments
        printf("You must give ONE command line argument, an int n\n");
        return 1;
    }

    const int n = atoi(argv[1]);    // Read in command line argument (as int)

    if (n < 1) {                    // Error if inputted n < 1
        printf("n must be an int >= 1\n");
        return 1;
    }

    // Allocate a Sieve of Eratosthenes, an array of bools
    // representing the primality of numbers 0 through n (inclusive)
    bool* is_prime_arr = (bool*) malloc((n+1) * sizeof(bool));

    if (!is_prime_arr) {
        printf("Failed to allocate array\n");
        return 1;
    }

    // All numbers are assumed prime initially
    for (int i=0; i<=n; i++) {
        is_prime_arr[i] = true;
    }

    // 0 and 1 are canonically not prime
    is_prime_arr[0] = false;
    is_prime_arr[1] = false;

    // Starting from 2, mark all multiples of each remaining prime as not prime
    // (see https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes for the visualization)
    //
    // Note: marking multiples of each number from 2 to n is inefficient; you can check just
    // from 2 to sqrt(n), as any composite number <= n would have a prime factor <= sqrt(n) :)
    for (int i=2; i*i<=n; i++) {

        if (is_prime_arr[i]) {                                          // A remaining prime (i)

            for (int multiple = 2*i; multiple <= n; multiple += i) {    // Mark all its multiples (2i, 3i...) not prime
                is_prime_arr[multiple] = false;
            }

        }
    }

    // Print n, then the primes (I'm not going to print 1 as a prime!)
    printf("%d\n", n);
    for (int i=0; i<=n; i++) {
        if (is_prime_arr[i]) {
            printf("%d\n", i);
        }
    }

    // Free the allocated sieve
    free(is_prime_arr);

    return 0;
}