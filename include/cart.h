#pragma once
#ifndef _CART_H_
#define _CART_H_

#include <stdint.h>

typedef struct mfr_cgb {
    uint8_t pad[0xb];
    char mfr_code[0x4];
    uint8_t flag;
} mfr_cgb;

typedef union title_mfr_cgb {
    char title[0x10];
    mfr_cgb mfr_cgb;
} title_mfr_cgb;

typedef struct cart_header {
    uint8_t entrypoint[0x4];
    uint8_t logo[0x30];
    title_mfr_cgb title_mfr_cgb;
    char new_lic_code[0x2];
    uint8_t sgb_flag;
    uint8_t cart_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t dest_code;
    uint8_t old_lic_code;
    uint8_t rom_ver;
    uint8_t checksum;
    uint8_t global_checksum[0x2];
} cart_header;

typedef struct cart {
    cart_header *header;
    uint8_t *data;
} cart;

cart *cart_read(const char *restrict rom);
void cart_debug(const cart *cart);

#endif