#include "inst.h"
#include <stdio.h>
#include <stdlib.h>

// Maps opcode --> instruction
static const inst instructions[0x100] = {
    [0x00] = {INS_NOP, 1, 1, AM_NONE, REG_NONE, REG_NONE, COND_NONE},
    [0xC3] = {INS_JMP, 4, 3, AM_IMM16, REG_NONE, REG_NONE, COND_NONE},
};

const inst *get_inst(u8 opcode) {
    const inst *inst = &instructions[opcode];
    if (inst->type == INS_NONE) {
        fprintf(stderr, "Instruction with opcode 0x%02x not yet implemented\n", opcode);
        exit(EXIT_FAILURE);
    }
    return inst;
}