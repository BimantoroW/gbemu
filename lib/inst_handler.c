#include "inst.h"
#include "cpu.h"
#include "mem.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void ins_hand_jp(cpu *cpu, mem *mem) {
    cpu->regs.pc = cpu->cur_data.src_data;
}

void ins_hand_jr(cpu *cpu, mem *mem) {
    switch (cpu->cur_inst->cond) {
        case COND_NONE:
            cpu->regs.pc += SIGN_EXTEND(cpu->cur_data.src_data);
            break;
        case COND_Z:
            if (CPU_GET_Z(cpu)) {
                cpu->regs.pc += SIGN_EXTEND(cpu->cur_data.src_data);
            }
            break;
        default:
            fprintf(stderr, "JR TYPE NOT YET IMPLEMENTED\n");
            exit(1);
            break;
    }
}

void ins_hand_xor(cpu *cpu, mem *mem) {
    u8 *dst_reg = (u8 *)cpu->cur_data.dst;
    u8 src_data = cpu->cur_data.src_data;
    u8 res = *dst_reg ^ src_data;
    *dst_reg = res;

    u8 z = res == 0 ? 1 : 0;
    CPU_SET_FLAGS(cpu, z, 0, 0, 0);
}

void ins_hand_nop(cpu *cpu, mem *mem) {

}

void ins_hand_cp(cpu *cpu, mem *mem) {
    u8 dst_val = *((u8 *)cpu->cur_data.dst);
    u8 src = cpu->cur_data.src_data;

    u8 z = (dst_val - src) == 0 ? 1 : 0;
    u8 n = 1;
    u8 h = ((dst_val & 0xf) < (src & 0xf)) ? 1 : 0;
    u8 c = (dst_val < src) ? 1 : 0;
    CPU_SET_FLAGS(cpu, z, n, h, c);
}