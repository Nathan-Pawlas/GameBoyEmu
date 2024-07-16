#ifndef CPU
#define CPU

#include <stdint.h>

union Register
{
	uint16_t reg;
	struct
	{
		uint8_t lo;
		uint8_t hi;
	};
};

enum Flags
{
	F_Z = 0x7,
	F_N = 0x6,
	F_H = 0x5,
	F_C = 0x4
};

class cpu
{
public:

private:
	//16bit Registers, 8 bit Hi/Lo segments
	Register AF;
	Register BC;
	Register DE;
	Register HL;
	//Special Registers, 16bit only
	uint16_t sp; //Stack Pointer
	uint16_t pc; //Program Counter
};

#endif