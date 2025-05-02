#pragma once
#ifndef _CART_H_
#define _CART_H_

#include "util.h"

typedef struct mfr_cgb {
    u8 pad[0xb];
    char mfr_code[0x4];
    u8 flag;
} mfr_cgb;

typedef union title_mfr_cgb {
    char title[0x10];
    mfr_cgb mfr_cgb;
} title_mfr_cgb;

typedef struct cart_header {
    u8 entrypoint[0x4];
    u8 logo[0x30];
    title_mfr_cgb title_mfr_cgb;
    char new_lic_code[0x2];
    u8 sgb_flag;
    u8 cart_type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 old_lic_code;
    u8 rom_ver;
    u8 checksum;
    u8 global_checksum[0x2];
} cart_header;

typedef struct cart {
    cart_header *header;
    u8 *data;
} cart;

cart *cart_load(const char *restrict rom);
void cart_debug(const cart *cart);
u8 cart_read(cart *cart, u16 addr);
void cart_write(cart *cart, u16 addr, u8 val);

#endif