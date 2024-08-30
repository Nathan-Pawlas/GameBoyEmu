#include "cpu.h"
#include "instructions.h"

void cpu::init(mmu *memory)
{
}

void cpu::fetch_instruction()
{
	/*opcode = mem->mem_read(pc);*/
	cur_inst = instruction_lookup(opcode);
}

void cpu::fetch_data()
{
}

void cpu::execute()
{
}

bool cpu::step()
{
	if (true)
	{
		fetch_instruction();
		fetch_data();
		execute();
	}
	return false;
}
