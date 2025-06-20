#include "instructions.h"
#include "cpu.h"
#include "gb.h"

//Table of all instructions
//{type, addr mode, reg 1, reg 2, cond, param}
instruction opcode_table[0x100] =
{   
    //0x0X
    /*0x00*/ {IN_NOP, AM_IMP},
    /*0x01*/ {IN_LD, AM_R_D16, RT_BC},
    /*0x02*/ {IN_LD, AM_MR_R, RT_BC, RT_A},
    /*0x03*/ {IN_INC, AM_R, RT_BC},
    /*0x04*/ {IN_INC, AM_R, RT_B},
    /*0x05*/ {IN_DEC, AM_R, RT_B},
    /*0x06*/ {IN_LD, AM_R_D8, RT_B},
    /*0x07*/ {IN_RLCA},
    /*0x08*/ {IN_LD, AM_A16_R, RT_NONE, RT_SP},
    /*0x09*/ {IN_ADD, AM_R_R, RT_HL, RT_BC},
    /*0x0A*/ {IN_LD, AM_R_MR, RT_A, RT_BC},
    /*0x0B*/ {IN_DEC, AM_R, RT_BC},
    /*0x0C*/ {IN_INC, AM_R, RT_C},
    /*0x0D*/ {IN_DEC, AM_R, RT_C},
    /*0x0E*/ {IN_LD, AM_R_D8, RT_C},
    /*0x0F*/ {IN_RRCA},
    
    //0x1X
    /*0x10*/ {IN_STOP},
    /*0x11*/ {IN_LD, AM_R_D16, RT_DE},
    /*0x12*/ {IN_LD, AM_MR_R, RT_DE, RT_A},
    /*0x13*/ {IN_INC, AM_R, RT_DE},
    /*0x14*/ {IN_INC, AM_R, RT_D},
    /*0x15*/ {IN_DEC, AM_R, RT_D},
    /*0x16*/ {IN_LD, AM_R_D8, RT_D},
    /*0x17*/ {IN_RLA},
    /*0x18*/ {IN_JR, AM_D8},
    /*0x19*/ {IN_ADD, AM_R_R, RT_HL, RT_DE},
    /*0x1A*/ {IN_LD, AM_R_MR, RT_A, RT_DE},
    /*0x1B*/ {IN_DEC, AM_R, RT_DE},
    /*0x1C*/ {IN_INC, AM_R, RT_E},
    /*0x1D*/ {IN_DEC, AM_R, RT_E},
    /*0x1E*/ {IN_LD, AM_R_D8, RT_E},
    /*0x1F*/ {IN_RRA},
     
    //0x2X
    /*0x20*/ {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NZ},
    /*0x21*/ {IN_LD, AM_R_D16, RT_HL},
    /*0x22*/ {IN_LD, AM_HLI_R, RT_HL, RT_A},
    /*0x23*/ {IN_INC, AM_R, RT_HL},
    /*0x24*/ {IN_INC, AM_R, RT_H},
    /*0x25*/ {IN_DEC, AM_R, RT_H},
    /*0x26*/ {IN_LD, AM_R_D8, RT_H},
    /*0x27*/ {IN_DAA},
    /*0x28*/ {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_Z},
    /*0x29*/ {IN_ADD, AM_R_R, RT_HL, RT_HL},
    /*0x2A*/ {IN_LD, AM_R_HLI, RT_A, RT_HL},
    /*0x2B*/ {IN_DEC, AM_R, RT_HL},
    /*0x2C*/ {IN_INC, AM_R, RT_L},
    /*0x2D*/ {IN_DEC, AM_R, RT_L},
    /*0x2E*/ {IN_LD, AM_R_D8, RT_L},
    /*0x2F*/ {IN_CPL},
     
    //0x3X
    /*0x30*/ {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NC},
    /*0x31*/ {IN_LD, AM_R_D16, RT_SP},
    /*0x32*/ {IN_LD, AM_HLD_R, RT_HL, RT_A},
    /*0x33*/ {IN_INC, AM_R, RT_SP},
    /*0x34*/ {IN_INC, AM_MR, RT_HL},
    /*0x35*/ {IN_DEC, AM_MR, RT_HL},
    /*0x36*/ {IN_LD, AM_MR_D8, RT_HL},
    /*0x37*/ {IN_SCF},
    /*0x38*/ {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_C},
    /*0x39*/ {IN_ADD, AM_R_R, RT_HL, RT_SP},
    /*0x3A*/ {IN_LD, AM_R_HLD, RT_A, RT_HL},
    /*0x3B*/ {IN_DEC, AM_R, RT_SP},
    /*0x3C*/ {IN_INC, AM_R, RT_A},
    /*0x3D*/ {IN_DEC, AM_R, RT_A},
    /*0x3E*/ {IN_LD, AM_R_D8, RT_A},
    /*0x3F*/ {IN_CCF},
    
    //0x4X 
    /*0x40*/ {IN_LD, AM_R_R, RT_B, RT_B},
    /*0x41*/ {IN_LD, AM_R_R, RT_B, RT_C},
    /*0x42*/ {IN_LD, AM_R_R, RT_B, RT_D},
    /*0x43*/ {IN_LD, AM_R_R, RT_B, RT_E},
    /*0x44*/ {IN_LD, AM_R_R, RT_B, RT_H},
    /*0x45*/ {IN_LD, AM_R_R, RT_B, RT_L},
    /*0x46*/ {IN_LD, AM_R_MR, RT_B, RT_HL},
    /*0x47*/ {IN_LD, AM_R_R, RT_B, RT_A},
    /*0x48*/ {IN_LD, AM_R_R, RT_C, RT_B},
    /*0x49*/ {IN_LD, AM_R_R, RT_C, RT_C},
    /*0x4A*/ {IN_LD, AM_R_R, RT_C, RT_D},
    /*0x4B*/ {IN_LD, AM_R_R, RT_C, RT_E},
    /*0x4C*/ {IN_LD, AM_R_R, RT_C, RT_H},
    /*0x4D*/ {IN_LD, AM_R_R, RT_C, RT_L},
    /*0x4E*/ {IN_LD, AM_R_MR, RT_C, RT_HL},
    /*0x4F*/ {IN_LD, AM_R_R, RT_C, RT_A},
    
    //0x5X 
    /*0x50*/ {IN_LD, AM_R_R,  RT_D, RT_B},
    /*0x51*/ {IN_LD, AM_R_R,  RT_D, RT_C},
    /*0x52*/ {IN_LD, AM_R_R,  RT_D, RT_D},
    /*0x53*/ {IN_LD, AM_R_R,  RT_D, RT_E},
    /*0x54*/ {IN_LD, AM_R_R,  RT_D, RT_H},
    /*0x55*/ {IN_LD, AM_R_R,  RT_D, RT_L},
    /*0x56*/ {IN_LD, AM_R_MR, RT_D, RT_HL},
    /*0x57*/ {IN_LD, AM_R_R,  RT_D, RT_A},
    /*0x58*/ {IN_LD, AM_R_R,  RT_E, RT_B},
    /*0x59*/ {IN_LD, AM_R_R,  RT_E, RT_C},
    /*0x5A*/ {IN_LD, AM_R_R,  RT_E, RT_D},
    /*0x5B*/ {IN_LD, AM_R_R,  RT_E, RT_E},
    /*0x5C*/ {IN_LD, AM_R_R,  RT_E, RT_H},
    /*0x5D*/ {IN_LD, AM_R_R,  RT_E, RT_L},
    /*0x5E*/ {IN_LD, AM_R_MR, RT_E, RT_HL},
    /*0x5F*/ {IN_LD, AM_R_R,  RT_E, RT_A},
     
    //0x6X
    /*0x60*/ {IN_LD, AM_R_R,  RT_H, RT_B},
    /*0x61*/ {IN_LD, AM_R_R,  RT_H, RT_C},
    /*0x62*/ {IN_LD, AM_R_R,  RT_H, RT_D},
    /*0x63*/ {IN_LD, AM_R_R,  RT_H, RT_E},
    /*0x64*/ {IN_LD, AM_R_R,  RT_H, RT_H},
    /*0x65*/ {IN_LD, AM_R_R,  RT_H, RT_L},
    /*0x66*/ {IN_LD, AM_R_MR, RT_H, RT_HL},
    /*0x67*/ {IN_LD, AM_R_R,  RT_H, RT_A},
    /*0x68*/ {IN_LD, AM_R_R,  RT_L, RT_B},
    /*0x69*/ {IN_LD, AM_R_R,  RT_L, RT_C},
    /*0x6A*/ {IN_LD, AM_R_R,  RT_L, RT_D},
    /*0x6B*/ {IN_LD, AM_R_R,  RT_L, RT_E},
    /*0x6C*/ {IN_LD, AM_R_R,  RT_L, RT_H},
    /*0x6D*/ {IN_LD, AM_R_R,  RT_L, RT_L},
    /*0x6E*/ {IN_LD, AM_R_MR, RT_L, RT_HL},
    /*0x6F*/ {IN_LD, AM_R_R,  RT_L, RT_A},
   
    //0x7X 
    /*0x70*/ {IN_LD, AM_MR_R,  RT_HL, RT_B},
    /*0x71*/ {IN_LD, AM_MR_R,  RT_HL, RT_C},
    /*0x72*/ {IN_LD, AM_MR_R,  RT_HL, RT_D},
    /*0x73*/ {IN_LD, AM_MR_R,  RT_HL, RT_E},
    /*0x74*/ {IN_LD, AM_MR_R,  RT_HL, RT_H},
    /*0x75*/ {IN_LD, AM_MR_R,  RT_HL, RT_L},
    /*0x76*/ {IN_HALT},
    /*0x77*/ {IN_LD, AM_MR_R,  RT_HL, RT_A},
    /*0x78*/ {IN_LD, AM_R_R,  RT_A, RT_B},
    /*0x79*/ {IN_LD, AM_R_R,  RT_A, RT_C},
    /*0x7A*/ {IN_LD, AM_R_R,  RT_A, RT_D},
    /*0x7B*/ {IN_LD, AM_R_R,  RT_A, RT_E},
    /*0x7C*/ {IN_LD, AM_R_R,  RT_A, RT_H},
    /*0x7D*/ {IN_LD, AM_R_R,  RT_A, RT_L},
    /*0x7E*/ {IN_LD, AM_R_MR, RT_A, RT_HL},
    /*0x7F*/ {IN_LD, AM_R_R,  RT_A, RT_A},
   
    //0x8X 
    /*0x80*/ {IN_ADD, AM_R_R, RT_A, RT_B},
    /*0x81*/ {IN_ADD, AM_R_R, RT_A, RT_C},
    /*0x82*/ {IN_ADD, AM_R_R, RT_A, RT_D},
    /*0x83*/ {IN_ADD, AM_R_R, RT_A, RT_E},
    /*0x84*/ {IN_ADD, AM_R_R, RT_A, RT_H},
    /*0x85*/ {IN_ADD, AM_R_R, RT_A, RT_L},
    /*0x86*/ {IN_ADD, AM_R_MR, RT_A, RT_HL},
    /*0x87*/ {IN_ADD, AM_R_R, RT_A, RT_A},
    /*0x88*/ {IN_ADC, AM_R_R, RT_A, RT_B},
    /*0x89*/ {IN_ADC, AM_R_R, RT_A, RT_C},
    /*0x8A*/ {IN_ADC, AM_R_R, RT_A, RT_D},
    /*0x8B*/ {IN_ADC, AM_R_R, RT_A, RT_E},
    /*0x8C*/ {IN_ADC, AM_R_R, RT_A, RT_H},
    /*0x8D*/ {IN_ADC, AM_R_R, RT_A, RT_L},
    /*0x8E*/ {IN_ADC, AM_R_MR, RT_A, RT_HL},
    /*0x8F*/ {IN_ADC, AM_R_R, RT_A, RT_A},
    
    //0x9X 
    /*0x90*/ {IN_SUB, AM_R_R, RT_A, RT_B},
    /*0x91*/ {IN_SUB, AM_R_R, RT_A, RT_C},
    /*0x92*/ {IN_SUB, AM_R_R, RT_A, RT_D},
    /*0x93*/ {IN_SUB, AM_R_R, RT_A, RT_E},
    /*0x94*/ {IN_SUB, AM_R_R, RT_A, RT_H},
    /*0x95*/ {IN_SUB, AM_R_R, RT_A, RT_L},
    /*0x96*/ {IN_SUB, AM_R_MR, RT_A, RT_HL},
    /*0x97*/ {IN_SUB, AM_R_R, RT_A, RT_A},
    /*0x98*/ {IN_SBC, AM_R_R, RT_A, RT_B},
    /*0x99*/ {IN_SBC, AM_R_R, RT_A, RT_C},
    /*0x9A*/ {IN_SBC, AM_R_R, RT_A, RT_D},
    /*0x9B*/ {IN_SBC, AM_R_R, RT_A, RT_E},
    /*0x9C*/ {IN_SBC, AM_R_R, RT_A, RT_H},
    /*0x9D*/ {IN_SBC, AM_R_R, RT_A, RT_L},
    /*0x9E*/ {IN_SBC, AM_R_MR, RT_A, RT_HL},
    /*0x9F*/ {IN_SBC, AM_R_R, RT_A, RT_A},
 
    //0xAX
    /*0xA0*/ {IN_AND, AM_R_R, RT_A, RT_B},
    /*0xA1*/ {IN_AND, AM_R_R, RT_A, RT_C},
    /*0xA2*/ {IN_AND, AM_R_R, RT_A, RT_D},
    /*0xA3*/ {IN_AND, AM_R_R, RT_A, RT_E},
    /*0xA4*/ {IN_AND, AM_R_R, RT_A, RT_H},
    /*0xA5*/ {IN_AND, AM_R_R, RT_A, RT_L},
    /*0xA6*/ {IN_AND, AM_R_MR, RT_A, RT_HL},
    /*0xA7*/ {IN_AND, AM_R_R, RT_A, RT_A},
    /*0xA8*/ {IN_XOR, AM_R_R, RT_A, RT_B},
    /*0xA9*/ {IN_XOR, AM_R_R, RT_A, RT_C},
    /*0xAA*/ {IN_XOR, AM_R_R, RT_A, RT_D},
    /*0xAB*/ {IN_XOR, AM_R_R, RT_A, RT_E},
    /*0xAC*/ {IN_XOR, AM_R_R, RT_A, RT_H},
    /*0xAD*/ {IN_XOR, AM_R_R, RT_A, RT_L},
    /*0xAE*/ {IN_XOR, AM_R_MR, RT_A, RT_HL},
    /*0xAF*/ {IN_XOR, AM_R_R, RT_A, RT_A},
   
    //0xBX 
    /*0xB0*/ {IN_OR, AM_R_R, RT_A, RT_B},
    /*0xB1*/ {IN_OR, AM_R_R, RT_A, RT_C},
    /*0xB2*/ {IN_OR, AM_R_R, RT_A, RT_D},
    /*0xB3*/ {IN_OR, AM_R_R, RT_A, RT_E},
    /*0xB4*/ {IN_OR, AM_R_R, RT_A, RT_H},
    /*0xB5*/ {IN_OR, AM_R_R, RT_A, RT_L},
    /*0xB6*/ {IN_OR, AM_R_MR, RT_A, RT_HL},
    /*0xB7*/ {IN_OR, AM_R_R, RT_A, RT_A},
    /*0xB8*/ {IN_CP, AM_R_R, RT_A, RT_B},
    /*0xB9*/ {IN_CP, AM_R_R, RT_A, RT_C},
    /*0xBA*/ {IN_CP, AM_R_R, RT_A, RT_D},
    /*0xBB*/ {IN_CP, AM_R_R, RT_A, RT_E},
    /*0xBC*/ {IN_CP, AM_R_R, RT_A, RT_H},
    /*0xBD*/ {IN_CP, AM_R_R, RT_A, RT_L},
    /*0xBE*/ {IN_CP, AM_R_MR, RT_A, RT_HL},
    /*0xBF*/ {IN_CP, AM_R_R, RT_A, RT_A},
    
    //0xCX
    /*0xC0*/ {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NZ},
    /*0xC1*/ {IN_POP, AM_R, RT_BC},
    /*0xC2*/ {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    /*0xC3*/ {IN_JP, AM_D16},
    /*0xC4*/ {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NZ},
    /*0xC5*/ {IN_PUSH, AM_R, RT_BC},
    /*0xC6*/ {IN_ADD, AM_R_D8, RT_A},
    /*0xC7*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00},
    /*0xC8*/ {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_Z},
    /*0xC9*/ {IN_RET},
    /*0xCA*/ {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_Z},
    /*0xCB*/ {IN_CB, AM_D8},
    /*0xCC*/ {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_Z},
    /*0xCD*/ {IN_CALL, AM_D16},
    /*0xCE*/ {IN_ADC, AM_R_D8, RT_A},
    /*0xCF*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x08},
    
    //0xDX
    /*0xD0*/ {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NC},
    /*0xD1*/ {IN_POP, AM_R, RT_DE},
    /*0xD3*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xD2*/ {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NC},
    /*0xD4*/ {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NC},
    /*0xD5*/ {IN_PUSH, AM_R, RT_DE},
    /*0xD6*/ {IN_SUB, AM_R_D8, RT_A},
    /*0xD7*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x10},
    /*0xD8*/ {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_C},
    /*0xD9*/ {IN_RETI},
    /*0xDA*/ {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_C},
    /*0xDB*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xDC*/ {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_C},
    /*0xDD*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xDE*/ {IN_SBC, AM_R_D8, RT_A},
    /*0xDF*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x18},
    
    //0xEX
    /*/0xE*/ 
    /*0xE0*/ {IN_LDH, AM_A8_R, RT_NONE, RT_A},
    /*0xE1*/ {IN_POP, AM_R, RT_HL},
    /*0xE2*/ {IN_LD, AM_MR_R, RT_C, RT_A},
    /*0xE3*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xE4*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xE5*/ {IN_PUSH, AM_R, RT_HL},
    /*0xE6*/ {IN_AND, AM_R_D8, RT_A},
    /*0xE7*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x20},
    /*0xE8*/ {IN_ADD, AM_R_D8, RT_SP},
    /*0xE9*/ {IN_JP, AM_R, RT_HL},
    /*0xEA*/ {IN_LD, AM_A16_R, RT_NONE, RT_A},
    /*0xEB*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xEC*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xED*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xEE*/ {IN_XOR, AM_R_D8, RT_A},
    /*0xEF*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x28},
    
    //0xFX
    /*0xF0*/ {IN_LDH, AM_R_A8, RT_A},
    /*0xF1*/ {IN_POP, AM_R, RT_AF},
    /*0xF2*/ {IN_LD, AM_R_MR, RT_A, RT_C},
    /*0xF3*/ {IN_DI},
    /*0xF4*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xF5*/ {IN_PUSH, AM_R, RT_AF},
    /*0xF6*/ {IN_OR, AM_R_D8, RT_A},
    /*0xF7*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x30},
    /*0xF8*/ {IN_LD, AM_HL_SPR, RT_HL, RT_SP},
    /*0xF9*/ {IN_LD, AM_R_R, RT_SP, RT_HL},
    /*0xFA*/ {IN_LD, AM_R_A16, RT_A},
    /*0xFB*/ {IN_EI},
    /*0xFC*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xFD*/{ IN_NOP }, //Place Holder: Should Never Be Called
    /*0xFE*/ {IN_CP, AM_R_D8, RT_A},
    /*0xFF*/ {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x38},

};

instruction* instruction_lookup(uint16_t opcode)
{
    //Check the instruction is valid
    if (opcode_table[opcode].type == IN_NOP && opcode != 0x00)
    {
        printf("UNKNOWN INSTRUCTION! %02x", opcode);
        exit(-1);
    }
    //Return pointer to the instructions definition
    return &opcode_table[opcode];
}

/////////////////////////////////////////////////
/*----------------PROCESSES--------------------*/
/////////////////////////////////////////////////
//Reference: https://rgbds.gbdev.io/docs/v0.8.0/gbz80.7
void set_flags(cpu* cur_cpu, uint8_t z, uint8_t n, uint8_t h, uint8_t c)
{
    if (z != -1)
        BIT_SET(cur_cpu->AF.lo, 7, z); //Set specified bit (7) to flag value (z)
    if (n != -1)
        BIT_SET(cur_cpu->AF.lo, 6, n);
    if (h != -1)
        BIT_SET(cur_cpu->AF.lo, 5, h);
    if (c != -1)
        BIT_SET(cur_cpu->AF.lo, 4, c);
}

static bool check_cond(cpu* cur_cpu)
{
    //https://gbdev.io/pandocs/CPU_Registers_and_Flags.html
    bool z = (cur_cpu->AF.lo >> 7) & 0x1;
    bool c = (cur_cpu->AF.lo >> 4) & 0x1;

    switch (cur_cpu->cur_inst->cond)
    {
    case CT_NONE: return true;
    case CT_C: return c;
    case CT_NC: return !c;
    case CT_Z: return z;
    case CT_NZ: return !z;
    }

    return false; //Should never reach
}

void stack_push(uint8_t data, cpu* cpu) {
    cpu->sptr--;
    cpu->mem->mem_write(cpu->sptr, data);
}

void stack_push16(uint16_t data, cpu* cpu) {
    stack_push((data >> 8) & 0xFF, cpu);
    stack_push(data & 0xFF, cpu);
}

uint8_t stack_pop(cpu* cpu) {
    return cpu->mem->mem_read(cpu->sptr++);
}

uint16_t stack_pop16(cpu* cpu) {
    uint16_t lo = stack_pop(cpu);
    uint16_t hi = stack_pop(cpu);

    return (hi << 8) | lo;
}

static void goto_addr(cpu* cpu, uint16_t addr, bool pushpc)
{
    if (check_cond(cpu))
    {
        if (pushpc)
        {
            gb::cycle(2);
            stack_push16(cpu->pc, cpu);
        }

        cpu->pc = addr;
        gb::cycle(1);
    }
}

void proc_none(cpu* cur_cpu)
{
    printf("%02x: \n", cur_cpu->opcode);
    std::cout << "\t INVALID INSTRUCTION!\n";
    exit(-1);
}

void proc_nop(cpu* cur_cpu)
{
    //No Operation
}

reg_type rt_lookup[] = {
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_HL,
    RT_A,
};

reg_type decode_reg(uint8_t reg)
{
    if (reg > 0b111)
    {
        return RT_NONE;
    }

    return rt_lookup[reg];
}

void proc_cb(cpu* cpu)
{
    uint8_t op = cpu->data;
    reg_type reg = decode_reg(op & 0b111);
    uint8_t bit = (op >> 3) & 0b111;
    uint8_t bit_op = (op >> 6) & 0b11;
    uint16_t reg_val = cpu->read_register(reg);

    gb::cycle(1);

    if (reg == RT_HL)
    {
        gb::cycle(2);
    }

    switch (bit_op)
    {
    case 1:
        //BIT
        set_flags(cpu, !(reg_val & (1 << bit)), 0, 1, -1);
        break;
    case 2:
        //RST
        reg_val &= ~(1 << bit);
        cpu->set_register(reg, reg_val);
        break;
    case 3:
        //SET
        reg_val |= (1 << bit);
        cpu->set_register(reg, reg_val);
        re;
    case 4:

    }
}

void proc_ld(cpu* cur_cpu)
{
    if (cur_cpu->dest_in_mem) //Load into Memory
    {
        if (cur_cpu->cur_inst->reg_2 >= RT_AF) //i.e. if it is a 16 bit reg
        {
            gb::cycle(1);
            cur_cpu->mem->mem_write16(cur_cpu->mem_dest, cur_cpu->data);
        }
        else
        {
            cur_cpu->mem->mem_write(cur_cpu->mem_dest, cur_cpu->data);
        }
        return;
    }

    if (cur_cpu->cur_inst->mode == AM_HL_SPR) //Special case
    {
        bool h = (cur_cpu->read_register(cur_cpu->cur_inst->reg_2) & 0xF) + (cur_cpu->data & 0xF) >= 0x10;
        bool c = (cur_cpu->read_register(cur_cpu->cur_inst->reg_2) & 0xFF) + (cur_cpu->data & 0xFF) >= 0x100;
        set_flags(cur_cpu, 0, 0, h, c);

        cur_cpu->set_register(cur_cpu->cur_inst->reg_1, (cur_cpu->read_register(cur_cpu->cur_inst->reg_2) + (uint8_t)cur_cpu->data));
        return;
    }

    cur_cpu->set_register(cur_cpu->cur_inst->reg_1, cur_cpu->data);
}

void proc_ldh(cpu* cpu)
{
    if (cpu->cur_inst->reg_1 == RT_A)
    {
        cpu->set_register(cpu->cur_inst->reg_1, cpu->mem->mem_read(0xFF00 | cpu->read_register(cpu->cur_inst->reg_2)));
    }
    else
    {
        cpu->mem->mem_write(0xFF00 | cpu->data, cpu->read_register(cpu->cur_inst->reg_1));
    }
    gb::cycle(1);
}

void proc_di(cpu* cur_cpu)
{
    cur_cpu->int_master_enabled = false;
}

void proc_xor(cpu* cur_cpu)
{
    cur_cpu->AF.hi ^= (cur_cpu->data & 0xFF);
    set_flags(cur_cpu, cur_cpu->AF.hi == 0, 0, 0, 0);
}

void proc_and(cpu* cur_cpu)
{
    cur_cpu->AF.hi = (cur_cpu->data & 0xFF);
    set_flags(cur_cpu, cur_cpu->AF.hi == 0, 0, 0, 0);
}

void proc_or(cpu* cur_cpu)
{
    cur_cpu->AF.hi |= (cur_cpu->data & 0xFF);
    set_flags(cur_cpu, cur_cpu->AF.hi == 0, 0, 0, 0);
}



void proc_call(cpu* cpu)
{
    goto_addr(cpu, cpu->data, true);
}

void proc_rst(cpu* cpu)
{
    goto_addr(cpu, cpu->cur_inst->param, true);
}

void proc_ret(cpu* cpu)
{
    if (cpu->cur_inst->cond != CT_NONE) gb::cycle(1);
    if (check_cond(cpu))
    {
        uint16_t lo = stack_pop(cpu);
        gb::cycle(1);
        uint16_t hi = stack_pop(cpu);
        gb::cycle(1);

        uint16_t addr = (hi << 8) | lo;
        cpu->pc = addr;
        gb::cycle(1);
    }
}

void proc_reti(cpu* cpu)
{
    cpu->int_master_enabled = true;
    proc_ret(cpu);
}

void proc_jp(cpu* cur_cpu)
{
    goto_addr(cur_cpu, cur_cpu->data, false);
}

void proc_jr(cpu* cpu)
{
    int8_t val = (int8_t)(cpu->data & 0xFF); //Signed 8bit address from Immediate
    uint16_t addr = cpu->pc + val;
    goto_addr(cpu, addr, false);
}

void proc_pop(cpu* cpu) //Pop only operates on 16bit values
{
    uint16_t value = stack_pop16(cpu);
    gb::cycle(2);

    cpu->set_register(cpu->cur_inst->reg_1, value);

    if (cpu->cur_inst->reg_1 == RT_AF)
    {
        cpu->set_register(RT_AF, value & 0xFFF0);
    }

}

void proc_push(cpu* cpu) //Push only operates on 16bit values
{
    uint8_t hi = ((cpu->read_register(cpu->cur_inst->reg_1) >> 8) & 0xFF);
    gb::cycle(1);
    stack_push(hi, cpu);
    uint8_t lo = (cpu->read_register(cpu->cur_inst->reg_1) & 0xFF);
    gb::cycle(1);
    stack_push(lo, cpu);

    gb::cycle(1);
}

void proc_inc(cpu* cpu)
{
    uint16_t val = cpu->read_register(cpu->cur_inst->reg_1) + 1;

    if (cpu->cur_inst->reg_1 >= RT_AF) //Check if the register is 16bits
    {
        gb::cycle(1);
    }

    if (cpu->cur_inst->reg_1 == RT_HL && cpu->cur_inst->mode == AM_MR)
    {
        val = cpu->mem->mem_read(cpu->read_register(RT_HL)) + 1;
        val &= 0xFF; //Mask out just the bottom byte incase of overflow (inc [HL] only increments 1 byte!)
        gb::cycle(1);
        cpu->mem->mem_write(cpu->read_register(RT_HL), val);
    }
    else
    {
        cpu->set_register(cpu->cur_inst->reg_1, val);
        val = cpu->read_register(cpu->cur_inst->reg_1);
    }


    if ((cpu->read_register(cpu->cur_inst->reg_1) & 0x03) == 0x03)
    {
        return;
    }

    set_flags(cpu, val == 0, 0, (val & 0x0F) == 0, -1);
}

void proc_dec(cpu* cpu)
{
    uint16_t val = cpu->read_register(cpu->cur_inst->reg_1) - 1;

    if (cpu->cur_inst->reg_1 >= RT_AF) //Check if the register is 16bits
    {
        gb::cycle(1);
    }

    if (cpu->cur_inst->reg_1 == RT_HL && cpu->cur_inst->mode == AM_MR)
    {
        val = cpu->mem->mem_read(cpu->read_register(RT_HL)) - 1;
        val &= 0xFF;
        gb::cycle(1);
        cpu->mem->mem_write(cpu->read_register(RT_HL), val);
    }
    else
    {
        cpu->set_register(cpu->cur_inst->reg_1, val);
        val = cpu->read_register(cpu->cur_inst->reg_1);
    }


    if ((cpu->read_register(cpu->cur_inst->reg_1) & 0x0B) == 0x0B)
    {
        return;
    }

    set_flags(cpu, val == 0, 1, (val & 0x0F) == 0x0F, -1);
}

void proc_add(cpu* cpu)
{
    uint16_t value = cpu->read_register(cpu->cur_inst->reg_1) + cpu->data;

    uint8_t z = 0; 
    uint8_t h = 0;
    uint8_t c = 0;

    if (cpu->cur_inst->reg_1 >= RT_AF)
    {
        gb::cycle(1);

        z = -1; //I.E. don't touch
        h = ((cpu->read_register(cpu->cur_inst->reg_1) & 0xFFF) + (cpu->data & 0xFFF)) > 0x00FF;
        c = ((uint32_t)cpu->read_register(cpu->cur_inst->reg_1) + (uint32_t)cpu->data) > 0xFFFF;
    }
    else
    {
        z = (value & 0xFF) == 0;
        h = ((cpu->read_register(cpu->cur_inst->reg_1) & 0xF) + (cpu->data & 0xF)) > 0x0F;
        c = ((uint32_t)cpu->read_register(cpu->cur_inst->reg_1) + (uint32_t)cpu->data) > 0xFF;
    }

    if (cpu->cur_inst->reg_1 == RT_SP)
    {
        value = cpu->read_register(cpu->cur_inst->reg_1) + (uint8_t)cpu->data;

        z = 0;
        h = ((cpu->read_register(cpu->cur_inst->reg_1) & 0xF) + (cpu->data & 0xF)) > 0x0F;
        c = ((uint32_t)cpu->read_register(cpu->cur_inst->reg_1) + (uint32_t)cpu->data) > 0xFF;
    }

    set_flags(cpu, z, 0, h, c);
    cpu->set_register(cpu->cur_inst->reg_1, value);
}

void proc_adc(cpu* cpu)
{
    uint16_t data = cpu->data;
    uint16_t a = cpu->read_register(RT_A);
    uint16_t c = BIT(cpu->read_register(RT_F), 4);

    cpu->set_register(RT_A, (a + data + c));

    set_flags(cpu, cpu->read_register(RT_A) == 0, 0, (a & 0xF) + (data & 0xF) + c > 0xF, a + data + c > 0xFF);
}

void proc_sub(cpu* cpu) //Only 1 byte sub instructions!
{
    uint16_t value = cpu->read_register(cpu->cur_inst->reg_1) - cpu->data;

    int z = value == 0;
    int h = ((int)(cpu->read_register(cpu->cur_inst->reg_1) &0xF) - (int)(cpu->data * 0xF)) < 0;
    int c = ((int)cpu->read_register(cpu->cur_inst->reg_1) - (int)cpu->data) < 0;

    set_flags(cpu, z, 1, h, c);
    cpu->set_register(cpu->cur_inst->reg_1, value);
}

void proc_sbc(cpu* cpu)
{
    uint16_t data = cpu->data;
    uint16_t a = cpu->read_register(cpu->cur_inst->reg_1);
    uint16_t c = BIT(cpu->read_register(RT_F), 4);

    int z = a - (data + c) == 0;
    int h = (a & 0xF) - (data & 0xF) - c < 0;
    int c_flag = a - data - c < 0;

    cpu->set_register(cpu->cur_inst->reg_1, (a - (data + c)));
    set_flags(cpu, z, 1, h, c_flag);

}

void proc_cp(cpu* cpu)
{
    int n = cpu->read_register(RT_A) - cpu->data;

    set_flags(cpu, n == 0, 1, (cpu->read_register(RT_A) & 0xF) - (cpu->data & 0xF) < 0, n < 0);
}

//Table of function ptrs to be returned to cpu
static inst_map im = {
    {IN_NOP, &proc_nop},
    {IN_LD, &proc_ld},
    {IN_JP, &proc_jp},
    {IN_DI, &proc_di},
    {IN_XOR, &proc_xor},
    {IN_CALL, &proc_call},
    {IN_LDH, &proc_ldh},
    {IN_CB, &proc_cb},
    {IN_JR, &proc_jr},
    {IN_POP, &proc_pop},
    {IN_PUSH, &proc_push},
    {IN_RET, &proc_ret},
    {IN_RETI, &proc_reti},
    {IN_RST, &proc_rst},
    {IN_INC, &proc_inc},
    {IN_DEC, &proc_dec},
    {IN_ADD, &proc_add},
    {IN_SUB, &proc_sub},
    {IN_ADC, &proc_adc},
    {IN_SBC, &proc_sbc},
    {IN_AND, &proc_and},
    {IN_OR, &proc_or},
    {IN_CP, &proc_cp},
    {IN_CB, &proc_cb},
};

IN_PROC process::get_proc(in_type type)
{
    if (im[type] != NULL)
        return im[type];
    return &proc_none;
}


