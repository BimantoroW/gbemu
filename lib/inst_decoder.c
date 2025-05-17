#include "inst.h"
#include "mem.h"
#include "cpu.h"
#include "inst_decoder.h"
#include <stdio.h>
#include <stdlib.h>

void ins_dec_jp(cpu *cpu, mem *mem) {
    u8 low = mem_read(mem, cpu->regs.pc);
    u8 high = mem_read(mem, cpu->regs.pc + 1);
    u16 addr = (high << 8) | low;
    cpu->regs.pc += 2;

    cpu->cur_data.dst_type = OP_REG16;
    cpu->cur_data.dst = &cpu->regs.pc;
    cpu->cur_data.src_data = addr;
}

void ins_dec_xor(cpu *cpu, mem *mem) {
    switch (cpu->cur_inst->src_type) {
        case OP_REG8:
            cpu->cur_data.src_data = *cpu_get_reg(cpu, cpu->cur_inst->src_reg);
            break;
        default:
            fprintf(stderr, "NOT YEY IMPLEMENTED\n");
            exit(1);
            break;
    }

    switch (cpu->cur_inst->dst_type) {
        case OP_REG8:
            cpu->cur_data.dst_type = OP_REG8;
            cpu->cur_data.dst = cpu_get_reg(cpu, cpu->cur_inst->dst_reg);
            break;
        default:
            fprintf(stderr, "NOT YEY IMPLEMENTED\n");
            exit(1);
            break;
    }
}

void ins_dec_jr(cpu *cpu, mem *mem) {
    u8 offset = mem_read(mem, cpu->regs.pc++);
    cpu->cur_data.dst_type = OP_REG16;
    cpu->cur_data.dst = &cpu->regs.pc;
    cpu->cur_data.src_data = offset;
}

void ins_dec_nop(cpu *cpu, mem *mem) {
    cpu->cur_data.dst_type = OP_NONE;
    cpu->cur_data.dst = NULL;
    cpu->cur_data.src_data = 0;
}

void ins_dec_cp(cpu *cpu, mem *mem) {
    u8 imm;
    switch (cpu->cur_inst->src_type) {
        case OP_IMM8:
            imm = mem_read(mem, cpu->regs.pc++);
            break;
        default:
            fprintf(stderr, "NOT YEY IMPLEMENTED\n");
            exit(1);
            break;
    }
    cpu->cur_data.dst_type = OP_REG8;
    cpu->cur_data.dst = &cpu->regs.a;
    cpu->cur_data.src_data = imm;
}