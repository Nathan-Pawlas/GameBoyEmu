#pragma once
#include "utils.h"
#include "mmu.h"
#include "instructions.h"


struct reg
{
	uint16_t data = 0;
	uint8_t hi = (data >> 8);
	uint8_t lo = (data & 0xFF);
};

class cpu
{
public:
	void init(mmu *memory);

	void fetch_instruction();
	void fetch_data();
	void execute();

	bool step();

	uint16_t read_register(reg_type rt);

public:
	bool halted = false;
	bool stepping = true;
	int test = 123;
private:
	reg AF;
	reg BC;
	reg DE;
	reg HL;
	uint16_t pc = 0x100;
	uint16_t sptr = 0x0;

	bool dest_in_mem;

	uint16_t data = 0;
	uint16_t mem_dest = 0;
	uint8_t opcode = 0x00;
	instruction *cur_inst = nullptr;

	mmu *mem;
};

