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
    const INST_DECODER decoder = inst_get_decoder(cpu->cur_inst->type);
    decoder(cpu, mem);
}

void cpu_execute(cpu *cpu, mem *mem) {
    cpu_debug(cpu, mem);
    const INST_HANDLER handler = inst_get_handler(cpu->cur_inst->type);
    handler(cpu, mem);
}