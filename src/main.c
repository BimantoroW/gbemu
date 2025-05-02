#include "emu.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [rom]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *rom = argv[1];

    if (emu_run(rom) != 0) {
        fprintf(stderr, "Emulation error\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}