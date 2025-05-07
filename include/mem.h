#pragma once
#ifndef _MEM_H_
#define _MEM_H_

#include "util.h"
#include "cart.h"

typedef struct mem {
    cart *cart;
} mem;

mem *mem_init(cart *cart);
u8 mem_read(mem *mem, u16 addr);
void mem_write(mem *mem, u16 addr, u8 val);

#endif