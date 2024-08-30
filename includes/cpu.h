#pragma once
#include "utils.h"
#include "instructions.h"
#include "mmu.h"

struct reg
{
	uint8_t hi;
	uint8_t lo;
	uint16_t full = hi | lo;
};

class cpu
{
public:
	void init(mmu *memory);

	void fetch_instruction();
	void fetch_data();
	void execute();

	bool step();

public:
	bool halted;
	bool stepping;


private:
	reg AF;
	reg BC;
	reg DE;
	reg HL;
	uint16_t pc;
	uint16_t sptr;

	uint16_t data;
	uint16_t mem_dest;
	uint8_t opcode;
	instruction *cur_inst;

	mmu *mem;
};