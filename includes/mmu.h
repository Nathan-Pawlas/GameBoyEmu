#pragma once
#include "utils.h"

//Source: https://gbdev.io/pandocs/The_Cartridge_Header.html
/*
	Cartridge layout
	Address Range: 0x0100 - 0x014F

	Entry Point: 100 - 103 -> 4bytes
	Logo: 104 - 133 -> 29 bytes
	Title: 134 - 143 -> 9 bytes
	CGB Flag: 143 -> 1 byte
	License: 144 - 145 -> 2bytes
	SGB Flag: 146 -> 1 byte
	Cart Type: 147 -> 1 byte
	ROM Size: 148 -> 1 byte
	RAM Size: 149 -> 1 byte
	Dest Code: 14A -> 1 byte
	Old License: 14B -> 1 byte
	ROM Version: 14C -> 1 byte
	Header Checksum: 14D -> 1byte
	Global Checksum: 14E - 14F -> 2 bytes
*/

typedef struct
{
	uint8_t		entry[4];
	uint8_t		logo[29];
	uint8_t		title[9];
	uint8_t		cgb_flag;
	uint16_t	license;
	uint8_t		sgb_flag;
	uint8_t		cart_type;
	uint8_t		rom_size;
	uint8_t		ram_size;
	uint8_t		dest_code;
	uint8_t		old_license;
	uint8_t		rom_version;
	uint8_t		head_checksum;
	uint16_t	global_checksum;
} header;

class mmu
{
public:

	bool load_rom(char *path_to_rom);

	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t value);

public:
	uint32_t rom_size;
	uint8_t *rom_data;
	header* rom_header;
};