#pragma once
#ifndef _INST_DEC_H_
#define _INST_DEC_H_

#include "cpu.h"

void ins_dec_nop(cpu *cpu, mem *mem);
void ins_dec_jr(cpu *cpu, mem *mem);
void ins_dec_xor(cpu *cpu, mem *mem);
void ins_dec_jp(cpu *cpu, mem *mem);
void ins_dec_cp(cpu *cpu, mem *mem);

#endif