#pragma once
#include "utils.h"
#include "instructions.h"
#include "mmu.h"
#include <unordered_map>

struct reg
{
	uint16_t data;
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

private:
	reg AF;
	reg BC;
	reg DE;
	reg HL;
	uint16_t pc;
	uint16_t sptr;

	bool dest_in_mem;

	uint16_t data;
	uint16_t mem_dest;
	uint8_t opcode;
	instruction *cur_inst;

	mmu *mem;
};

