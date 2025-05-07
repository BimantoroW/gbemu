#pragma once
#ifndef _CPU_H_
#define _CPU_H_

#include "mem.h"
#include "inst.h"

typedef struct cpu_regs {
    u8 a, f, b, c, d, e, h, l;
    u16 sp, pc;
} cpu_regs;

typedef struct cpu {
    cpu_regs regs;

    // Current instruction data
    const inst *cur_inst;
    u16 imm_data;
} cpu;

cpu *cpu_init();
void cpu_fetch(cpu *cpu, mem *mem);
void cpu_read_data(cpu *cpu, mem *mem);
void cpu_execute(cpu *cpu, mem *mem);

#endif