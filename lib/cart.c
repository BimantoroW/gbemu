#include <stdio.h>
#include <stdlib.h>
#include "cart.h"

static const char *CART_TYPES[] = {
    [0x00] = "ROM ONLY",
    [0x01] = "MBC1",
    [0x02] = "MBC1+RAM",
    [0x03] = "MBC1+RAM+BATTERY",
    [0x05] = "MBC2",
    [0x06] = "MBC2+BATTERY",
    [0x08] = "ROM+RAM",
    [0x09] = "ROM+RAM+BATTERY",
    [0x0B] = "MMM01",
    [0x0C] = "MMM01+RAM",
    [0x0D] = "MMM01+RAM+BATTERY",
    [0x0F] = "MBC3+TIMER+BATTERY",
    [0x10] = "MBC3+TIMER+RAM+BATTERY",
    [0x11] = "MBC3",
    [0x12] = "MBC3+RAM",
    [0x13] = "MBC3+RAM+BATTERY",
    [0x19] = "MBC5",
    [0x1A] = "MBC5+RAM",
    [0x1B] = "MBC5+RAM+BATTERY",
    [0x1C] = "MBC5+RUMBLE",
    [0x1D] = "MBC5+RUMBLE+RAM",
    [0x1E] = "MBC5+RUMBLE+RAM+BATTERY",
    [0x20] = "MBC6",
    [0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    [0xFC] = "POCKET CAMERA",
    [0xFD] = "BANDAI TAMA5",
    [0xFE] = "HuC3",
    [0xFF] = "HuC1+RAM+BATTERY",
};

static const uint8_t *RAM_SIZES[] = {
    [0x00] = 0,
    [0x02] = 8,
    [0x03] = 32,
    [0x04] = 128,
    [0x05] = 64,
};

static const char *DEST_CODES[] = {
    "Japan",
    "Overseas"
};

cart *cart_read(const char *restrict rom) {
    FILE *fp = fopen(rom, "r");

    // Get rom size
    fseek(fp, 0, SEEK_END);
    long rom_size = ftell(fp);
    rewind(fp);

    // Allocate data for the rom
    uint8_t *rom_data = malloc(rom_size);
    fread(rom_data, rom_size, 1, fp);
    fclose(fp);

    // Allocate rom
    cart *cart = malloc(sizeof(cart));
    cart->data = rom_data;
    cart->header = rom_data + 0x100;

    // Verify checksum
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - rom_data[address] - 1;
    }

    if (checksum != cart->header->checksum) {
        fprintf(stderr, "ROM checksum doesn't match\n");
        exit(EXIT_FAILURE);
    }

    return cart;
}

void cart_debug(const cart *cart) {
    printf("Title\t\t\t: %s\n", cart->header->title_mfr_cgb.title);
    printf("License Code\t\t: %.2s\n", cart->header->new_lic_code);
    printf("SGB Flag\t\t: $%02x\n", cart->header->sgb_flag);
    printf("Cartridge Type\t\t: %s\n", CART_TYPES[cart->header->cart_type]);
    printf("ROM Size\t\t: %d KiB\n", 32 * (1 << cart->header->rom_size));
    printf("RAM Size\t\t: %d KiB\n", RAM_SIZES[cart->header->ram_size]);
    printf("Destination Code\t: %s\n", DEST_CODES[cart->header->dest_code]);
    printf("Version Number\t\t: 0x%02x\n", cart->header->rom_ver);
    printf("Header Checksum\t\t: 0x%02x (passed)\n", cart->header->checksum);
}