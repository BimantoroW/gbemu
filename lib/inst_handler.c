#include "inst.h"
#include "cpu.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void handle_jmp(cpu *cpu, mem *mem) {
    cpu->regs.pc = cpu->imm_data;
}

void handle_nop(cpu *cpu, mem *mem) {

}

const INST_HANDLER inst_handlers[] = {
    [INS_NOP] = handle_nop,
    [INS_JMP] = handle_jmp,
};

const INST_HANDLER inst_get_handler(inst_type type) {
    INST_HANDLER handler = inst_handlers[type];
    if (handler == NULL) {
        fprintf(stderr, "Decoder for instruction not yet implemented: %d\n", type);
        exit(1);
    }
    return handler;
}