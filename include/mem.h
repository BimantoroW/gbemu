#pragma once
#ifndef _MEM_H_
#define _MEM_H_

#include "util.h"
#include "emu.h"

// typedef struct mem {

// } mem;

u8 mem_read(emu_gb *emu, u16 addr);
void mem_write(emu_gb *emu, u16 addr, u8 val);

#endif