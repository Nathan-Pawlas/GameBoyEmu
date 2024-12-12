#include "cpu.h"
#include "gb.h"

void cpu::init(mmu *memory)
{
	mem = memory;
	pc = 0x100;
}

void cpu::fetch_instruction()
{
	opcode = mem->mem_read(pc);
	cur_inst = instruction_lookup(opcode);
}

void cpu::fetch_data()
{
	mem_dest = 0;
	dest_in_mem = false;

	//Handle Data for each Address Mode
	if (cur_inst == NULL) {
		return;
	}
	switch (cur_inst->mode)
	{
	default: exit(-1);

	case AM_IMP: pc++; return;

	case AM_R:
		data = read_register(cur_inst->reg_1);
		pc++;
		return;

	case AM_R_D8:
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		pc+=2;
		return;

	case AM_D16:
	{
		uint16_t lo = mem->mem_read(pc +  1);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 2);
		gb::cycle(1);

		data =  lo | (hi << 8);
		pc += 3; //curr_inst | lo_8bits | hi_8bits | next_inst
		return;
	}
	}
}

void cpu::execute()
{
	IN_PROC proc;
	proc = process::get_proc(cur_inst->type);
	if (proc == NULL)
	{
		printf("UNKNOWN INSTRUCTION! %02x", opcode);
		exit(-1);
	}
	proc(this);
}

bool cpu::step()
{
	if (!halted)
	{
		uint16_t temp_pc = pc;
		fetch_instruction();
		fetch_data();
		printf("Executing Instruction: %02x   PC: %02x\n", opcode, temp_pc);
		execute();
		return true;
	}
	return false;
}

uint16_t cpu::read_register(reg_type rt)
{
	switch (rt)
	{
	case RT_A: return AF.hi;
	case RT_F: return AF.lo;
	case RT_B: return BC.hi;
	case RT_C: return BC.lo;
	case RT_D: return DE.hi;
	case RT_E: return DE.lo;
	case RT_H: return HL.hi;
	case RT_L: return HL.lo;
	case RT_AF: return AF.full;
	case RT_BC: return BC.full;
	case RT_DE: return DE.full;
	case RT_HL: return HL.full;
	case RT_PC: return pc;
	case RT_SP: return sptr;
	default: return 0;
	}
}

