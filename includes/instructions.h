#pragma once
#include "utils.h"

class cpu; //Forward decleration

enum cond_type //Control Flow Conditions
{
	CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
};

enum in_type //Instruction Set found here: https://izik1.github.io/gbops/index.html
{
	IN_NOP,
	IN_LD,
	IN_INC,
	IN_DEC,
	IN_RLCA,
	IN_ADD,
	IN_RRCA,
	IN_STOP,
	IN_RLA,
	IN_JR,
	IN_RRA,
	IN_DAA,
	IN_CPL,
	IN_SCF,
	IN_CCF,
	IN_HALT,
	IN_ADC,
	IN_SUB,
	IN_SBC,
	IN_AND,
	IN_XOR,
	IN_OR,
	IN_CP,
	IN_POP,
	IN_JP,
	IN_PUSH,
	IN_RET,
	IN_CB,
	IN_CALL,
	IN_RETI,
	IN_LDH,
	IN_JPHL,
	IN_DI,
	IN_EI,
	IN_RST,	
	IN_ERR,
	IN_RLC,
	IN_RRC,
	IN_RL,
	IN_RR,
	IN_SLA,
	IN_SRA,
	IN_SWAP,
	IN_SRL,
	IN_BIT,
	IN_RES,
	IN_SET,
};

enum addr_mode //What kind of reg load/write
{
	//Note Load syntax: LD Dest, Value
	AM_IMP, //Imperative (i.e. nothing)
	AM_R_D16, //16 bits to Reg
	AM_R_R,	//Reg to Reg
	AM_MR_R, //Reg to Mem (addr in reg)
	AM_R,
	AM_R_D8, //8bits to Reg
	AM_R_MR,
	AM_R_HLI,
	AM_HLI_R,
	AM_R_HLD,
	AM_HLD_R,
	AM_R_A8, //Reg AF(hi) to Reg
	AM_A8_R,
	AM_HL_SPR, //Stack Ptr to Reg HL
	AM_D16,
	AM_D8,
	AM_D16_R,
	AM_MR_D8,
	AM_MR,
	AM_A16_R,
	AM_R_A16,
};

enum reg_type //See cpu.h for layout of registers
{
	RT_NONE,
	RT_A, //8 bit Registers
	RT_F,
	RT_B,
	RT_C,
	RT_D,
	RT_E,
	RT_H,
	RT_L,
	RT_AF, //16 bit Unioned Registers
	RT_BC,
	RT_DE,
	RT_HL,
	RT_SP,
	RT_PC,
};

typedef struct
{
	in_type type;
	addr_mode mode;
	reg_type reg_1;
	reg_type reg_2;
	cond_type cond;
	uint8_t param;
} instruction;

instruction* instruction_lookup(uint16_t opcode);

typedef void (*IN_PROC)(cpu*);

typedef std::map<in_type, IN_PROC> inst_map;

class process //Effictively a "function pointer" class for the cpu
{
public:
	static IN_PROC get_proc(in_type type);
};