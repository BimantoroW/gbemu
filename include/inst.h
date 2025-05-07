#pragma once
#ifndef _INST_H_
#define _INST_H_

#include "util.h"
#include "mem.h"

typedef struct cpu cpu;

typedef u16 (*INST_DECODER)(cpu *, mem *);
typedef void (*INST_HANDLER)(cpu *, mem *);

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

typedef enum addr_mode {
    AM_NONE,
    AM_REG_REG,
    AM_REG_IMM8,
    AM_REG_IMM16,
    AM_REG_MEM,
    AM_MEM_IMM8,
    AM_MEM_REG,
    AM_IMM8,
    AM_IMM16,
} addr_mode;

typedef enum inst_type {
    INS_NONE,
    INS_NOP,
    INS_JMP,
    INS_CP,
} inst_type;

typedef struct inst {
    inst_type type;
    u8 cycles;
    u8 length;
    addr_mode mode;
    reg_type dst_reg;
    reg_type src_reg;
    inst_cond cond;
} inst;

inst *inst_disass_next(u8 *code);
const inst *inst_get(u8 opcode);
const INST_DECODER inst_get_decoder(inst_type type);
const INST_HANDLER inst_get_handler(inst_type type);

#endif