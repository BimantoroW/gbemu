#pragma once
#ifndef _INST_H_
#define _INST_H_

#include "util.h"

typedef enum inst_cond {
    COND_NONE,
    COND_Z,
} inst_cond;

typedef enum reg_type {
    REG_NONE,
    REG_A,
    REG_F,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
} reg_type;

typedef enum op_type {
    OP_NONE,
    OP_REG,
    OP_IMM,
    OP_MEM,
} op_type;

typedef enum inst_type {
    INS_NONE,
    INS_NOP,
    INS_JMP,
} inst_type;

typedef struct inst {
    inst_type type;
    u8 cycles;
    u8 length;
    op_type dst_type;
    op_type src_type;
    reg_type dst_reg;
    reg_type src_reg;
    inst_cond cond;
} inst;

inst inst_disass_next(u8 *code);

#endif