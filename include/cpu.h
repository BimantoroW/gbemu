#pragma once
#ifndef _CPU_H_
#define _CPU_H_

#include "mem.h"
#include "inst.h"

#define CPU_SET_FLAGS(cpu, z, n, h, c) (cpu->regs.f = (z << 7) | (n << 6) | (h << 5) | (c << 4))
#define CPU_GET_Z(cpu) ((cpu->regs.f >> 7) & 1)
#define CPU_GET_N(cpu) ((cpu->regs.f >> 6) & 1) 
#define CPU_GET_H(cpu) ((cpu->regs.f >> 5) & 1) 
#define CPU_GET_C(cpu) ((cpu->regs.f >> 4) & 1) 

// flags:
//  bit 7: zero
//  bit 6: subtraction
//  bit 5: half carry
//  bit 4: carry
typedef struct cpu_regs {
    u8 a, f, b, c, d, e, h, l;
    u16 sp, pc;
} cpu_regs;

typedef struct cpu {
    cpu_regs regs;

    // Current instruction data
    const inst *cur_inst;
    inst_data cur_data;
} cpu;

cpu *cpu_init();
void cpu_fetch_and_decode(cpu *cpu, mem *mem);
void cpu_execute(cpu *cpu, mem *mem);

#endif