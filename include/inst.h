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

typedef enum addr_mode {
    AM_NONE = 0,
    AM_REG8_REG8,
    AM_REG8_IMM8,
    AM_REG8_IMM16,
    AM_REG8_MEM,
    AM_REG16_IMM16,
    AM_REG16_IMM8,
    AM_MEM_IMM8,
    AM_MEM_REG,
} addr_mode;

typedef enum inst_type {
    INS_NONE = 0,
    INS_NOP,
    INS_JR,
    INS_JMP,
    INS_CP,
} inst_type;

typedef enum dst_type {
    DST_NONE = 0,
    DST_REG8,
    DST_REG16,
    DST_MEM,
} dst_type;

typedef struct inst {
    u8 opcode;
    inst_type type;
    u8 cycles;
    u8 length;
    addr_mode mode;
    reg_type dst_reg;
    reg_type src_reg;
    inst_cond cond;
} inst;

typedef struct inst_data {
    dst_type dst_type;
    union {
        u16 *u16;
        u8 *u8;
    } dst;
    u16 src_data;
} inst_data;

inst *inst_disass_next(u8 *code);
const inst *inst_get(u8 opcode);
const INST_DECODER inst_get_decoder(inst_type type);
const INST_HANDLER inst_get_handler(inst_type type);
const char *inst_get_name(inst_type type);

#endif