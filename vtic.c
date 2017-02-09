
#include <stdio.h>

#define ERR_ARGC 1 << 0

int main(int argc, char *argv[]) {

        // Argument checking
        if (argc > 2) {
                printf("Error: too many arguments");
                return ERR_ARGC;
        }

        return 0;
}
