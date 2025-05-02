#include "inst.h"
#include <stdio.h>
#include <stdlib.h>

// Maps opcode --> instruction
static const inst instructions[0x100] = {
    [0x00] = {INS_NOP, 1, 1, OP_NONE, OP_NONE, REG_NONE, REG_NONE, COND_NONE},
    [0xC3] = {INS_JMP, 4, 3, OP_MEM, OP_NONE, REG_NONE, REG_NONE, COND_NONE},
};

inst *get_inst(u8 opcode) {
    inst *inst = &instructions[opcode];
    if (inst->type == INS_NONE) {
        fprintf(stderr, "Instruction with opcode 0x%02x not yet implemented\n", opcode);
        exit(EXIT_FAILURE);
    }
    return inst;
}