#include <stdio.h>
#include <stdlib.h>     // atoi()

int main(int argc, char* argv[]) {

    const int n = atoi(argv[1]);    // Read in command line argument (as int)
    printf("%d", n);

    return 0;
}