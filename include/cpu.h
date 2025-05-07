#pragma once
#ifndef _CPU_H_
#define _CPU_H_

#include "mem.h"

typedef struct cpu_regs {
    u8 a, f, b, c, d, e, h, l;
    u16 sp, pc;
} cpu_regs;

typedef struct cpu {
    cpu_regs regs;

    // Current instruction
    u8 cur_opcode;
    u16 imm_data;
} cpu;

void cpu_init(cpu *cpu);
void cpu_fetch(cpu *cpu, mem *mem);
void cpu_read_data(cpu *cpu, mem *mem);
void cpu_execute(cpu *cpu, mem *mem);

#endif