
#ifndef OPCODES_H
#define OPCODES_H
#include <iostream>
#include <fstream>
using namespace std;
enum insnType
{
    LOAD = 1,
    ALU = 2,
    BR = 3,
    HALT = 4,
    NOP = 5
};


const uint16_t NUM_PIPE_STAGES = 3;
//const uint16_t NUM_INSN_TYPES = 3;
//LDI RDst, #Value
const uint16_t LDI = 0x01;
const uint16_t ADDI = 0x02;
const uint16_t BNE = 0x03;
const uint16_t HLT = 0x04;

const uint16_t MASK_INSN = 0xF;
const uint16_t MASK_RDst = 0xF << 4;
const uint16_t MASK_RSrc = 0xF << 8;
const uint16_t MASK_ADDImmValue = 0xF << 12;
const uint16_t MASK_BROffset = 0xF << 12;
const uint16_t MASK_LDImmValue = 0xFF << 8;

const uint16_t R0 = 0x00;
const uint16_t R1 = 0x01;
const uint16_t R2 = 0x02;
const uint16_t R3 = 0x03;
const uint16_t R4 = 0x04;
#endif