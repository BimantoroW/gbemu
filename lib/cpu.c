#include "cpu.h"
#include "inst.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

static void cpu_debug(cpu *cpu, mem *mem) {
    printf("CPU state\n");
    printf("    Current instruction : %s\n", inst_get_name(cpu->cur_inst->type));
    printf("    PC                  : 0x%04hx\n", cpu->regs.pc);
    printf("    Immediate           : 0x%04hx\n", cpu->imm_data);
    puts("");
}

cpu *cpu_init() {
    cpu *cpu = malloc(sizeof(struct cpu));
    bzero(cpu, sizeof(struct cpu)); 
    cpu->regs.pc = 0x0100;
    return cpu;
}

void cpu_fetch(cpu *cpu, mem *mem) {
    u8 opcode = mem_read(mem, cpu->regs.pc++);
    cpu->cur_inst = inst_get(opcode);
}

void cpu_read_data(cpu *cpu, mem *mem) {
    const INST_DECODER decoder = inst_get_decoder(cpu->cur_inst->type);
    cpu->imm_data = decoder(cpu, mem);
}

void cpu_execute(cpu *cpu, mem *mem) {
    cpu_debug(cpu, mem);
    const INST_HANDLER handler = inst_get_handler(cpu->cur_inst->type);
    handler(cpu, mem);
}