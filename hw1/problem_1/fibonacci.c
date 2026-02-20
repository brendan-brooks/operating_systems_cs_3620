#include <stdio.h>
#include <stdlib.h>     // atoi()

int main(int argc, char* argv[]) {

    if (argc != 2) {                // Check number of command line arguments
        printf("You must give ONE command line argument, an int n");
        return 1;
    }

    const int n = atoi(argv[1]);    // Read in command line argument (as int)

    if (n < 1 || n > 92) {          // Error if inputted n < 1 (or if n too large: overflow)
        printf("n must be an int between 1 and 92");
        return 1;
    }

    long long a = 0;
    long long b = 1;

    // Fibonacci loop
    for (int i=0; i<=n; i++) {

        printf("%lld\n", a);      // Newline following each int

        long long temp = a + b;
        a = b;
        b = temp;
    }

    return 0;
}