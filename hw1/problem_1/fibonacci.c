#include <stdio.h>
#include <stdlib.h>     // atoi()

int main(int argc, char* argv[]) {

    const int n = atoi(argv[1]);            // Read in command line argument (as int)

    if (n < 1) {                            // Error if inputted n < 1
        printf("n must be >= 1");
        return 1;
    }

    printf("%d", n);

    return 0;
}