#include <stdio.h>
#include <stdlib.h>     // atoi()

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

    return 0;
}