#include "emu.h"
#include "cart.h"
#include "cpu.h"
#include <stdio.h>
#include <strings.h>

void emu_init(emu_gb *emu, const char *restrict rom) {
    bzero(emu, sizeof(emu_gb));
    cart *cart = cart_load(rom);
    emu->cpu = cpu_init();
    emu->mem = mem_init(cart);
}

int emu_run(const char *restrict rom) {
    emu_gb emu;
    emu_init(&emu, rom);
    cart_debug(emu.mem->cart);
    puts("");

    while (1) {
        cpu_fetch(emu.cpu, emu.mem);
        cpu_read_data(emu.cpu, emu.mem);
        cpu_execute(emu.cpu, emu.mem);
    }
    printf("Running %s...\n", emu.mem->cart->header->title_mfr_cgb.title);
    cart_debug(emu.mem->cart);
    return 0;
}