#pragma once
#ifndef _INST_H_
#define _INST_H_

#include "util.h"
#include "mem.h"

typedef struct cpu cpu;

typedef void (*INST_DECODER)(cpu *, mem *);
typedef void (*INST_HANDLER)(cpu *, mem *);

typedef enum inst_cond {
    COND_NONE = 0,
    COND_Z,
    COND_NZ,
    COND_C,
    COND_NC,
} inst_cond;

typedef enum reg_type {
    REG_NONE = 0,
    REG_A,
    REG_F,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_PC,
    REG_SP,
} reg_type;

typedef enum op_type {
    OP_NONE = 0,
    OP_REG8,
    OP_REG16,
    OP_IMM8,
    OP_IMM16,
    OP_MEM,
} op_type;

typedef enum inst_type {
    INS_NONE = 0,
    INS_NOP,
    INS_LD,
    INS_INC,
    INS_DEC,
    INS_ADD,
    INS_STOP,
    INS_JR,
    INS_HALT,
    INS_ADC,
    INS_SUB,
    INS_SBC,
    INS_AND,
    INS_XOR,
    INS_OR,
    INS_CP,
    INS_RET,
    INS_POP,
    INS_JP,
    INS_CALL,
    INS_PUSH,
    INS_LDH
} inst_type;

typedef struct inst {
    u8 opcode;
    u8 type;
    u8 cycles;
    u8 length;

    u8 dst_type;
    u8 dst_reg;

    u8 src_type;
    u8 src_reg;

    u8 cond;

    INST_DECODER decoder;
    INST_HANDLER handler;
} inst;

typedef struct inst_data {
    void *dst;
    u8 dst_type;
    u16 src_data;
} inst_data;

inst *inst_disass_next(u8 *code);
const inst *inst_get(u8 opcode);
const char *inst_get_name(inst_type type);

#endif