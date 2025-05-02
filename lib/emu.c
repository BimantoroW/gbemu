#include "emu.h"
#include "cart.h"
#include <stdio.h>
#include <strings.h>

emu_gb gEmu;

void emu_init(const char *restrict rom) {
    bzero(&gEmu, sizeof(emu_gb));
    gEmu.cart = cart_read(rom);
}

int emu_run(const char *restrict rom) {
    emu_init(rom);
    printf("Running %s...\n", gEmu.cart->header->title_mfr_cgb.title);
    cart_debug(gEmu.cart);
    return 0;
}