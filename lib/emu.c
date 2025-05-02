#include "emu.h"
#include "cart.h"
#include <stdio.h>
#include <strings.h>

emu_gb gEmu;

void emu_init(void) {
    bzero(&gEmu, sizeof(emu_gb));
}

int emu_run(const char *restrict rom) {
    emu_init();
    gEmu.cart = cart_read(rom);
    printf("Running %s...\n", gEmu.cart->header->title_mfr_cgb.title);
    cart_debug(gEmu.cart);
    return 0;
}