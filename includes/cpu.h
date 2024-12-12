#pragma once
#include "utils.h"
#include "mmu.h"
#include "instructions.h"

//Registers are unioned struct of Hi and Lo bits
// 0x00 + 0x00
// |hi|   |lo|
// ---full----
union reg
{
	uint16_t full;
	struct
	{
		uint8_t lo;
		uint8_t hi;
	};
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
    void set_register(reg_type rt, uint16_t data);

public:
	bool halted = false;
	bool stepping = true;
	int test = 123;

	reg AF;
	reg BC;
	reg DE;
	reg HL;
	uint16_t pc = 0x100;
	uint16_t sptr = 0x0;

	bool dest_in_mem;
    bool int_master_enabled;

	uint16_t data = 0;
	uint16_t mem_dest = 0;
	uint8_t opcode = 0x00;
	instruction *cur_inst = nullptr;

	mmu *mem;

private:
    const char* inst_name[47] = {
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "POP",
    "JP",
    "PUSH",
    "RET",
    "CB",
    "CALL",
    "RETI",
    "LDH",
    "JPHL",
    "DI",
    "EI",
    "RST",
    "IN_ERR",
    "IN_RLC",
    "IN_RRC",
    "IN_RL",
    "IN_RR",
    "IN_SLA",
    "IN_SRA",
    "IN_SWAP",
    "IN_SRL",
    "IN_BIT",
    "IN_RES",
    "IN_SET"
    };
};

