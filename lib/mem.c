#include "mem.h"
#include "cart.h"
#include <stdio.h>
#include <stdlib.h>

mem *mem_init(cart *cart) {
    mem *mem = malloc(sizeof(struct mem));
    mem->cart = cart;
    return mem;
}

u8 mem_read(mem *mem, u16 addr) {
    if (addr < 0x8000) {
        return cart_read(mem->cart, addr);
    }
    perror("mem_read");
    exit(1);
}

void mem_write(mem *mem, u16 addr, u8 val) {
    if (addr < 0x8000) {
        cart_write(mem->cart, addr, val);
        return;
    }
    perror("mem_write");
    exit(1);
}