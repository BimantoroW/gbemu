#include "cpu.h"
#include "inst.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

static void cpu_debug(cpu *cpu, mem *mem) {
    printf("CPU state\n");
    printf("    Current instruction : %s\n", inst_get_name(cpu->cur_inst->type));
    printf("    Opcode              : 0x%02hx\n", cpu->cur_inst->opcode);
    printf("    PC                  : 0x%04hx\n", cpu->regs.pc);
    printf("    Immediate           : 0x%04hx\n", cpu->cur_data.src_data);
    printf("    Flags               : 0x%02hx\n", cpu->regs.f);
    puts("");
}

cpu *cpu_init() {
    cpu *cpu = malloc(sizeof(struct cpu));
    bzero(cpu, sizeof(struct cpu)); 
    cpu->regs.pc = 0x0100;
    return cpu;
}

void cpu_fetch_and_decode(cpu *cpu, mem *mem) {
    u8 opcode = mem_read(mem, cpu->regs.pc++);
    cpu->cur_inst = inst_get(opcode);
    if (cpu->cur_inst->decoder == NULL) {
        fprintf(stderr, "Decoder for instruction not yet implemented: %s\n", inst_get_name(cpu->cur_inst->type));
        exit(1);
    }
    cpu->cur_inst->decoder(cpu, mem);
}

void cpu_execute(cpu *cpu, mem *mem) {
    cpu_debug(cpu, mem);
    if (cpu->cur_inst->handler == NULL) {
        fprintf(stderr, "Handler for instruction not yet implemented: %s\n", inst_get_name(cpu->cur_inst->type));
        exit(1);
    }
    cpu->cur_inst->handler(cpu, mem);
}

u8 *cpu_get_reg(cpu *cpu, reg_type type) {
    switch (type) {
        case REG_A: return &cpu->regs.a; break;
        case REG_F: return &cpu->regs.f; break;
        case REG_B: return &cpu->regs.b; break;
        case REG_C: return &cpu->regs.c; break;
        case REG_D: return &cpu->regs.d; break;
        case REG_E: return &cpu->regs.e; break;
        case REG_H: return &cpu->regs.h; break;
        case REG_L: return &cpu->regs.l; break;
        case REG_NONE:
        default:
            fprintf(stderr, "INVALID REGISTER\n");
            exit(1);
            break;
    }
}