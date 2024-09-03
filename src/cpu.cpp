#include "cpu.h"
#include "instructions.h"
#include "gb.h"

void cpu::init(mmu *memory)
{
	mem = memory;
}

void cpu::fetch_instruction()
{
	opcode = mem->mem_read(pc + 1);
	cur_inst = instruction_lookup(opcode);
}

void cpu::fetch_data()
{
	mem_dest = 0;
	dest_in_mem = false;

	//Handle Data for each Address Mode
	switch (cur_inst->mode)
	{
	default: 
		std::cerr << "Unknown Address Mode ----------\n ";
		printf("\tInstruction: %02x  PC: %02x", opcode, pc);
		exit(-1);
	case AM_IMP: pc++; return;
	case AM_R:
		data = read_register(cur_inst->reg_1);
		return;
	case AM_R_D8:
		data = mem->mem_read(pc);
		gb::cycle(1);
		pc++;
		return;
	case AM_R_D16:
	{
		int16_t lo = mem->mem_read(pc);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 1);
		gb::cycle(1);

		data = (hi << 8) | lo;
		pc += 2;
		return;
	}
	case AM_D16:
	{
		uint16_t lo = mem->mem_read(pc);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 1);
		gb::cycle(1);

		data = (hi << 8) | lo;
		pc += 2;
		return;
	}
	}
}

void cpu::execute()
{
	IN_PROC proc;
	proc = process::get_proc(cur_inst->type);
	proc();
}

bool cpu::step()
{
	if (!halted)
	{
		uint16_t temp_pc = pc;
		fetch_instruction();
		fetch_data();
		printf("Executing Opcode: %02x   PC: %02x\n", opcode, temp_pc);
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
	case RT_AF: return AF.data;
	case RT_BC: return BC.data;
	case RT_DE: return DE.data;
	case RT_HL: return HL.data;
	case RT_PC: return pc;
	case RT_SP: return sptr;
	default: return 0;
	}
}