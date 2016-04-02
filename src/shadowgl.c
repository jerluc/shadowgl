#include <stdio.h>
#include "runtime.h"

int main(int argc, char* argv[]) {
    char* filename;

    if (argc == 1)
        filename = "main.lua";
    else
        filename = argv[1];

    if (run_program(filename) != 0)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}
