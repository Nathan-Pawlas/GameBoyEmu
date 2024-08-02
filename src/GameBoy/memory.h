#ifndef MEMORY
#define MEMORY

#include <stdint.h>

class Memory {
public:
	Memory();

	void LoadRom(const char* file_path);

public:
	uint8_t ROM[0x8000]; //Cartridge Memory 8K

private:

};

#endif