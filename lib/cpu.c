#include "cpu.h"
#include <strings.h>

void cpu_init(cpu *cpu) {
    bzero(cpu, sizeof(struct cpu)); 
    cpu->regs.pc = 0x0100;
}

void cpu_fetch(cpu *cpu, mem *mem) {
    u8 opcode = mem_read(mem, cpu->regs.pc++);
    cpu->cur_opcode = opcode;
}

void cpu_read_data(cpu *cpu, mem *mem);
void cpu_execute(cpu *cpu, mem *mem);