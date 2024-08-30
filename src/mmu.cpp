#include "mmu.h"


void mmu::debug_print_header()
{
	printf("Cartridge Loaded:\n");
	printf("\t Title		: %s\n", rom_header->title);
	printf("\t Type		: %2.2X (%s)\n", rom_header->cart_type, get_rom_type(rom_header->cart_type));
	printf("\t ROM Size	: %d KB\n", 32 << rom_header->rom_size);
	printf("\t RAM Size	: %2.2X\n", rom_header->ram_size);
	printf("\t LIC Code	: %2.2X (%s)\n", rom_header->license, get_license(rom_header->license));
	printf("\t ROM Vers	: %2.2X\n", rom_header->rom_version);

	uint16_t x = 0;
	for (uint16_t i = 0x0134; i <= 0x014C; i++) {
		x = x - rom_data[i] - 1;
	}

	printf("\t Checksum	: %2.2X (%s)\n", rom_header->head_checksum, (x & 0xFF) ? "PASSED" : "FAILED");
}

bool mmu::load_rom(const char* path_to_rom)
{
	snprintf(filename, sizeof(filename), "%s", path_to_rom);
	//Open rom
	FILE* fptr = fopen(path_to_rom, "r");

	if (!fptr)
	{
		std::cerr << "Failed to open "<< path_to_rom << std::endl;
		return false;
	}
	std::cout << "Opened: " << path_to_rom << std::endl;

	//Find how big rom is
	fseek(fptr, 0, SEEK_END);
	rom_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	//Copy rom data into memory
	rom_data = (uint8_t *)malloc(rom_size);
	fread(rom_data, rom_size, 1, fptr);
	fclose(fptr);

	rom_header = (header*)(rom_data + 0x0100); //copy header contents into variable
	rom_header->title[15] = 0;

	debug_print_header();

	return true;
}

//MMU
uint8_t mmu::mem_read(uint16_t address)
{
	if (address < 0x8000) //Reading from ROM
		return rom_data[address];

	NO_IMPL
}

void mmu::mem_write(uint16_t address, uint8_t value)
{
	if (address < 0x8000) //Write to Cart ROM
	{
		NO_IMPL
	}

	NO_IMPL
}


