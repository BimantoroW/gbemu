#include "inst.h"
#include "mem.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

u16 indec_jmp(cpu *cpu, mem *mem) {
    u8 low = mem_read(mem, cpu->regs.pc);
    u8 high = mem_read(mem, cpu->regs.pc + 1);
    u16 addr = (high << 8) | low;
    cpu->regs.pc += 2;
    return addr;
}

u16 indec_nop(cpu *cpu, mem *mem) {
    return 0;
}

const INST_DECODER inst_decoders[] = {
    [INS_NOP] = indec_nop,
    [INS_JMP] = indec_jmp,
};

const INST_DECODER inst_get_decoder(inst_type type) {
    INST_DECODER decoder = inst_decoders[type];
    if (decoder == NULL) {
        fprintf(stderr, "Decoder for instruction not yet implemented: %d\n", type);
        exit(1);
    }
    return decoder;
}