#include "inst.h"
#include "inst_handler.h"
#include "inst_decoder.h"
#include <stdio.h>
#include <stdlib.h>

// Maps opcode --> instruction
static const inst instructions[0x100] = {
    [0x00] = {0x00, INS_NOP, 1, 1, OP_NONE, REG_NONE, OP_NONE, REG_NONE, COND_NONE, ins_dec_nop, ins_hand_nop},
    [0x18] = {0x18, INS_JR, 3, 2, OP_REG16, REG_PC, OP_IMM8, REG_NONE, COND_NONE, ins_dec_jr, ins_hand_jr},
    [0x28] = {0x28, INS_JR, 3, 2, OP_REG16, REG_PC, OP_IMM8, REG_NONE, COND_Z, ins_dec_jr, ins_hand_jr},
    [0xAF] = {0xAF, INS_XOR, 3, 2, OP_REG8, REG_A, OP_REG8, REG_A, COND_NONE, ins_dec_xor, ins_hand_xor},
    [0xC3] = {0xC3, INS_JP, 4, 3, OP_REG16, REG_PC, OP_IMM16, REG_NONE, COND_NONE, ins_dec_jp, ins_hand_jp},
    [0xFE] = {0xFE, INS_CP, 2, 2, OP_REG8, REG_A, OP_IMM8, REG_NONE, COND_NONE, ins_dec_cp, ins_hand_cp},
};

static const char *inst_names[] = {
    [INS_NOP] = "NOP",
    [INS_LD] = "LD",
    [INS_INC] = "INC",
    [INS_DEC] = "DEC",
    [INS_ADD] = "ADD",
    [INS_STOP] = "STOP",
    [INS_JR] = "JR",
    [INS_HALT] = "HALT",
    [INS_ADC] = "ADC",
    [INS_SUB] = "SUB",
    [INS_SBC] = "SBC",
    [INS_AND] = "AND",
    [INS_XOR] = "XOR",
    [INS_OR] = "OR",
    [INS_CP] = "CP",
    [INS_RET] = "RET",
    [INS_POP] = "POP",
    [INS_JP] = "JP",
    [INS_CALL] = "CALL",
    [INS_PUSH] = "PUSH",
    [INS_LDH] = "LDH",
};

const inst *inst_get(u8 opcode) {
    const inst *inst = &instructions[opcode];
    if (inst->type == INS_NONE) {
        fprintf(stderr, "Instruction with opcode 0x%02x not yet implemented\n", opcode);
        exit(EXIT_FAILURE);
    }
    return inst;
}

const char *inst_get_name(inst_type type) {
    return inst_names[type];
}