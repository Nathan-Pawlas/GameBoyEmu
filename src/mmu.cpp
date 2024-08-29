#include "mmu.h"

bool mmu::load_rom(char* path_to_rom)
{
	//Open rom
	FILE* fptr = fopen(path_to_rom, "r");

	if (!fptr)
	{
		std::cerr << "Failed to open %s"<< path_to_rom << std::endl;
		return false;
	}

	//Find how big rom is
	fseek(fptr, 0, SEEK_END);
	rom_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	//Copy rom data into memory
	rom_data = (uint8_t *)malloc(rom_size);
	fread(rom_data, rom_size, 1, fptr);
	fclose(fptr);

	rom_header = (header*)(rom_data + 0x0100); //copy header contents into variable

	return true;
}
