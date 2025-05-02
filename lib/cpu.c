#include "cpu.h"
#include <strings.h>

void cpu_init(cpu *cpu) {
    bzero(cpu, sizeof(struct cpu)); 
    cpu->regs.pc = 0x0100;
}

void cpu_fetch(emu_gb *emu) {
    u8 opcode = mem_read(emu, emu->cpu->regs.pc++);
    emu->cpu->cur_opcode = opcode;
}

void cpu_read_data(cpu *cpu);
void cpu_execute(cpu *cpu);