#include "cpu.h"
#include "gb.h"

void cpu::init(mmu *memory)
{
	mem = memory;
	pc = 0x100;
	AF.full = 0x0000;
	BC.full = 0x0000;
	DE.full = 0x0000;
	HL.full = 0x0000;
}

void cpu::fetch_instruction()
{
	opcode = mem->mem_read(pc);
	cur_inst = instruction_lookup(opcode);
}

void cpu::fetch_data()
{
	//NOTE: this is just FETCHING the data, WRITING is handled in EXECUTION
	//i.e. AM_R_R = r1 = r2; So we are just assigning DATA as whatever is in R2, no touching R1!!!
	mem_dest = 0;
	dest_in_mem = false;

	//Handle Data for each Address Mode
	if (cur_inst == NULL) {
		return;
	}
	switch (cur_inst->mode)
	{
	default:
		printf("UNKNOWN ADDR MODE FOR OPCODE: %02x\n", opcode);
		exit(-1);

	case AM_IMP: pc++; return;

	case AM_R_R:
		data = read_register(cur_inst->reg_2);
		pc++;
		return;

	case AM_MR_R: //r2 -> mem @ r1;
		data = read_register(cur_inst->reg_2);
		dest_in_mem = true; //So execution knows if we are writing to memory or a register
		mem_dest = read_register(cur_inst->reg_1);

		if (cur_inst->reg_1 == RT_C) //https://rgbds.gbdev.io/docs/v0.8.0/gbz80.7#LDH__C_,A
			mem_dest |= 0xFF00;

		pc++;
		return;

	case AM_R:
		data = read_register(cur_inst->reg_1);
		pc++;
		return;

	case AM_R_D8:
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		pc+=2;
		return;

	case AM_R_MR:
	{
		uint16_t addr = read_register(cur_inst->reg_2);
		if (cur_inst->reg_2 == RT_C) https://rgbds.gbdev.io/docs/v0.8.0/gbz80.7#LDH_A,_C_
		addr |= 0xff00;
		data = mem->mem_read(addr);
		gb::cycle(1);
		pc++;
		return;
	}

	case AM_R_HLI:
		data = mem->mem_read(read_register(RT_HL));
		gb::cycle(1);
		HL.full = read_register(RT_HL) + 1;
		pc++;
		return;

	case AM_HLI_R:
		data = read_register(cur_inst->reg_2);
		dest_in_mem = true;
		mem_dest = read_register(RT_HL);
		HL.full = read_register(RT_HL) + 1;
		pc++;
		return;

	case AM_R_HLD:
		data = mem->mem_read(read_register(RT_HL));
		gb::cycle(1);
		HL.full = read_register(RT_HL) - 1;
		pc++;
		return;

	case AM_HLD_R:
		data = read_register(cur_inst->reg_2);
		dest_in_mem = true;
		mem_dest = read_register(RT_HL);
		HL.full = read_register(RT_HL) - 1;
		pc++;
		return;

	case AM_A8_R:
		mem_dest = mem->mem_read(pc + 1) | 0xFF00; //https://rgbds.gbdev.io/docs/v0.8.0/gbz80.7#LDH__n16_,A
		dest_in_mem = true;
		gb::cycle(1);
		data = read_register(cur_inst->reg_2);
		pc += 2;
		return;

	case AM_R_A8:
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		pc += 2;
		return;

	//Special Case for LD HL, SP + e8 (e8 is taken as an immediate value)
	//https://rgbds.gbdev.io/docs/v0.8.0/gbz80.7#LD_HL,SP+e8
	case AM_HL_SPR:
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		pc += 2;
		return;

	case AM_D8:
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		pc += 2;
		return;

	case AM_R_D16:
	{
		uint16_t lo = mem->mem_read(pc + 1);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 2);
		gb::cycle(1);
		data = lo | (hi << 8);
		pc += 3;
		return;
	}

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

	case AM_A16_R:
	case AM_D16_R:
	{
		uint16_t lo = mem->mem_read(pc + 1);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 2);
		gb::cycle(1);

		mem_dest = lo | (hi << 8);
		dest_in_mem = true;
		data = read_register(cur_inst->reg_2);
		pc += 3;
		return;
	}

	case AM_MR_D8:
	{
		data = mem->mem_read(pc + 1);
		gb::cycle(1);
		mem_dest = read_register(cur_inst->reg_1);
		dest_in_mem = true;
		pc += 2;
		return;
	}

	case AM_MR:
		mem_dest = read_register(cur_inst->reg_1);
		dest_in_mem = true;
		data = mem->mem_read(mem_dest);
		gb::cycle(1);
		pc++;
		return;

	case AM_R_A16:
	{
		uint16_t lo = mem->mem_read(pc + 1);
		gb::cycle(1);
		uint16_t hi = mem->mem_read(pc + 2);
		gb::cycle(1);

		uint16_t addr = lo | (hi << 8);
		data = mem->mem_read(addr);
		gb::cycle(1);
		pc += 3;
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
		printf("%04x: %7s (%02x %02x %02x) AF:%04x  BC:%04x  DE:%04x\n",
			temp_pc, inst_name[cur_inst->type], opcode,
			mem->mem_read(temp_pc + 1), mem->mem_read(temp_pc + 2),
			read_register(RT_AF), read_register(RT_BC), read_register(RT_DE));
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

