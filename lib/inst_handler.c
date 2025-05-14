#include "inst.h"
#include "cpu.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

void handle_jmp(cpu *cpu, mem *mem) {
    cpu->regs.pc = cpu->cur_data.src_data;
}

void handle_jr(cpu *cpu, mem *mem) {
    switch (cpu->cur_inst->cond) {
        case COND_Z:
            if (CPU_GET_Z(cpu)) {
                cpu->regs.pc += cpu->cur_data.src_data;
            }
            break;
        default:
            fprintf(stderr, "JR TYPE NOT YET IMPLEMENTED\n");
            exit(1);
            break;
    }
}

void handle_nop(cpu *cpu, mem *mem) {

}

void handle_cp(cpu *cpu, mem *mem) {
    u8 dst_reg = *(cpu->cur_data.dst.u8);
    u8 src = cpu->cur_data.src_data;

    u8 z = (dst_reg - src) == 0 ? 1 : 0;
    u8 n = 1;
    u8 h = ((dst_reg & 0xf) < (src & 0xf)) ? 1 : 0;
    u8 c = (dst_reg < src) ? 1 : 0;
    CPU_SET_FLAGS(cpu, z,  n, h, c);
}

const INST_HANDLER inst_handlers[] = {
    [INS_NOP] = handle_nop,
    [INS_JR] = handle_jr,
    [INS_JMP] = handle_jmp,
    [INS_CP] = handle_cp,
};

const INST_HANDLER inst_get_handler(inst_type type) {
    INST_HANDLER handler = inst_handlers[type];
    if (handler == NULL) {
        fprintf(stderr, "Handler for instruction not yet implemented: %s\n", inst_get_name(type));
        exit(1);
    }
    return handler;
}