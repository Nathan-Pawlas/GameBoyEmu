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
	uint8_t		logo[0x30];
	uint8_t		title[16];
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

/*
	Memory Map
	0x0000 - 0x3FFF ROM0				Cartridge	
	0x4000 - 0x7FFF ROMX (switchable)	Cartridge
	0x8000 - 0x9FFF VRAM				
	0xA000 - 0xBFFF SRAM				Cartridge
	0xC000 - 0xCFFF WRAM0				
	0xD000 - 0xDFFF WRAMX				
	0xE000 - 0xFDFF ECHO				Reserved
	0xFE00 - 0xFE9F OAM (Object Attribute Memory)
	0xFEA0 - 0xFEFF UNUSED				Reserved
	0xFF00 - 0xFF7F I/O
	0xFF80 - 0xFFFE HRAM (internal cpu RAM)
	0xFFFF			Interrupt Enable Flags
*/
class mmu
{
public:
	void debug_print_header();
	bool load_rom(const char *path_to_rom);

	uint8_t mem_read(uint16_t address);
	void mem_write(uint16_t address, uint8_t value);
	uint8_t mem_read16(uint16_t address);
	void mem_write16(uint16_t address, uint16_t value);

public:
	char filename[1024];
	uint32_t rom_size;
	uint8_t *rom_data;
	header* rom_header;

private:
	//Lookup tables for debug printing
	const char* get_rom_type(int type) {
		const char* ROM_TYPES[28] = {
			"ROM ONLY",
			"MBC1",
			"MBC1+RAM",
			"MBC1+RAM+BATTERY",
			"MBC2",
			"MBC2+BATTERY",
			"ROM+RAM",
			"ROM+RAM+BATTERY",
			"MMM01",
			"MMM01+RAM",
			"MMM01+RAM+BATTERY",
			"MBC3+TIMER+BATTERY",
			"MBC3+TIMER+RAM+BATTERY",
			"MBC3",
			"MBC3+RAM",
			"MBC3 + RAM + BATTERY",
			"MBC5",
			"MBC5+RAM",
			"MBC5+RAM+BATTERY",
			"MBC5+RUMBLE",
			"MBC5+RUMBLE+RAM",
			"MBC5+RUMBLE+RAM+BATTERY",
			"MBC6",
			"MBC7+SENSOR+RUMBLE+RAM+BATTERY",
			"POCKET CAMERA",
			"BANDAI TAMA5",
			"HuC3",
			"HuC1+RAM+BATTERY"
		};

		if (type <= 28)
		{
			return ROM_TYPES[type];
		}

		return "UNKNOWN";
	};

	const char* get_license(uint8_t hex_code)
	{
		switch (hex_code)
		{
		case 0x00: return "None";
		case 0x01: return "Nintendo R&D1";
		case 0x08: return "Capcom";
		case 0x13: return "Electronic Arts";
		case 0x18: return "Hudson Soft";
		case 0x19: return "b-ai";
		case 0x20: return "kss";
		case 0x22: return "pow";
		case 0x24: return "PCM Complete";
		case 0x25: return "san-x";
		case 0x28: return "Kemco Japan";
		case 0x29: return "seta";
		case 0x30: return "Viacom";
		case 0x31: return "Nintendo";
		case 0x32: return "Bandai";
		case 0x33: return "Ocean/Acclaim";
		case 0x34: return "Konami";
		case 0x35: return "Hector";
		case 0x37: return "Taito";
		case 0x38: return "Hudson";
		case 0x39: return "Banpresto";
		case 0x41: return "Ubi Soft";
		case 0x42: return "Atlus";
		case 0x44: return "Malibu";
		case 0x46: return "angel";
		case 0x47: return "Bullet-Proof";
		case 0x49: return "irem";
		case 0x50: return "Absolute";
		case 0x51: return "Acclaim";
		case 0x52: return "Activision";
		case 0x53: return "American sammy";
		case 0x54: return "Konami";
		case 0x55: return "Hi tech entertainment";
		case 0x56: return "LJN";
		case 0x57: return "Matchbox";
		case 0x58: return "Mattel";
		case 0x59: return "Milton Bradley";
		case 0x60: return "Titus";
		case 0x61: return "Virgin";
		case 0x64: return "LucasArts";
		case 0x67: return "Ocean";
		case 0x69: return "Electronic Arts";
		case 0x70: return "Infogrames";
		case 0x71: return "Interplay";
		case 0x72: return "Broderbund";
		case 0x73: return "sculptured";
		case 0x75: return "sci";
		case 0x78: return "THQ";
		case 0x79: return "Accolade";
		case 0x80: return "misawa";
		case 0x83: return "lozc";
		case 0x86: return "Tokuma Shoten Intermedia";
		case 0x87: return "Tsukuda Original";
		case 0x91: return "Chunsoft";
		case 0x92: return "Video system";
		case 0x93: return "Ocean/Acclaim";
		case 0x95: return "Varie";
		case 0x96: return "Yonezawa/s’pal";
		case 0x97: return "Kaneko";
		case 0x99: return "Pack in soft";
		case 0xA4: return "Konami (Yu-Gi-Oh!)";
		default:
			break;
		}
		return "UNKNOWN";
	};
};