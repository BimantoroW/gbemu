#include "emu.h"
#include "cart.h"
#include <stdio.h>
#include <strings.h>

void emu_init(emu_gb *emu, const char *restrict rom) {
    bzero(emu, sizeof(emu_gb));
    emu->cart = cart_load(rom);
}

int emu_run(const char *restrict rom) {
    emu_gb emu;
    emu_init(&emu, rom);
    printf("Running %s...\n", emu.cart->header->title_mfr_cgb.title);
    cart_debug(emu.cart);
    return 0;
}