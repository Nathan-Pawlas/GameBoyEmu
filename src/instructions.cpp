#include <instructions.h>

instruction opcode_table[0x100] =
{
	{IN_NOP, AM_IMP},

};

instruction* instruction_lookup(uint8_t opcode)
{
	return &opcode_table[0x00];
}