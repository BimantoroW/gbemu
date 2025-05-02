#include "mem.h"
#include "cart.h"
#include <stdio.h>
#include <stdlib.h>

u8 mem_read(emu_gb *emu, u16 addr) {
    if (addr < 0x8000) {
        return cart_read(emu->cart, addr);
    }
    perror("mem_read");
    exit(1);
}
void mem_write(emu_gb *emu, u16 addr, u8 val) {
    if (addr < 0x8000) {
        cart_write(emu->cart, addr, val);
        return;
    }
    perror("mem_write");
    exit(1);
}