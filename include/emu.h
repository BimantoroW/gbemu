#pragma once
#ifndef _EMU_H_
#define _EMU_H_

#include "cpu.h"
#include "mem.h"
#include "cart.h"

typedef struct emu_gb {
    cpu *cpu;
    mem *mem;
    cart *cart;
} emu_gb;

void emu_init(void);
int emu_run(const char *restrict rom);

#endif