#include "cpu.h"
#include "instructions.h"

void cpu::init(mmu *memory)
{
}

void cpu::fetch_instruction()
{
}

void cpu::fetch_data()
{
}

void cpu::execute()
{
}

bool cpu::step()
{
	if (!halted)
	{
		fetch_instruction();
		fetch_data();
		execute();
	}
	return false;
}
