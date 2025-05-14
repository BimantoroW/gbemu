#include "inst.h"
#include "mem.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

void indec_jmp(cpu *cpu, mem *mem) {
    u8 low = mem_read(mem, cpu->regs.pc);
    u8 high = mem_read(mem, cpu->regs.pc + 1);
    u16 addr = (high << 8) | low;
    cpu->regs.pc += 2;

    cpu->cur_data.dst_type = DST_REG16;
    cpu->cur_data.dst.u16 = (u16 *)&cpu->regs.pc;
    cpu->cur_data.src_data = addr;
}

void indec_jr(cpu *cpu, mem *mem) {
    u8 offset = mem_read(mem, cpu->regs.pc++);
    cpu->cur_data.dst_type = DST_REG16;
    cpu->cur_data.dst.u16 = (u16 *)&cpu->regs.pc;
    cpu->cur_data.src_data = offset;
}

void indec_nop(cpu *cpu, mem *mem) {
    cpu->cur_data.dst_type = DST_NONE;
    cpu->cur_data.dst.u16 = NULL;
    cpu->cur_data.src_data = 0;
}

void indec_cp(cpu *cpu, mem *mem) {
    u8 imm;
    switch (cpu->cur_inst->mode) {
        case AM_REG8_IMM8:
            imm = mem_read(mem, cpu->regs.pc++);
            cpu->cur_data.dst_type = DST_REG8;
            cpu->cur_data.dst.u8 = (u8 *)&cpu->regs.a;
            cpu->cur_data.src_data = imm;
            break;
        default:
            fprintf(stderr, "NOT YEY IMPLEMENTED\n");
            exit(1);
            break;
    }
}

const INST_DECODER inst_decoders[] = {
    [INS_NOP] = indec_nop,
    [INS_JR] = indec_jr,
    [INS_JMP] = indec_jmp,
    [INS_CP] = indec_cp,
};

const INST_DECODER inst_get_decoder(inst_type type) {
    INST_DECODER decoder = inst_decoders[type];
    if (decoder == NULL) {
        fprintf(stderr, "Decoder for instruction not yet implemented: %s\n", inst_get_name(type));
        exit(1);
    }
    return decoder;
}