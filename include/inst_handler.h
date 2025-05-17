#pragma once
#ifndef _INST_HAND_H_
#define _INST_HAND_H_

#include "cpu.h"

void ins_hand_nop(cpu *cpu, mem *mem);
void ins_hand_jr(cpu *cpu, mem *mem);
void ins_hand_xor(cpu *cpu, mem *mem);
void ins_hand_jp(cpu *cpu, mem *mem);
void ins_hand_cp(cpu *cpu, mem *mem);

#endif