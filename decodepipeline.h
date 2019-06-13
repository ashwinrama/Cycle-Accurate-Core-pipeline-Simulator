#ifndef DECODE_H
#define DECODE_H
#include "core_opcodes.h"
#include "fetchpipeline.h"

class decodeStage
{
public:
    uint16_t registerFile[4];

    decodeStage()
    {
        cout << "Initializing decode" << endl;
        for (int i = 0; i < 4; i++)
        {
            registerFile[i] = 0;
        }
        PC = 0;
        PC_Offset = 0;
        RDst = 0;
        RSrc0_Value = 0;
        RSrc1_Value = 0;
        ImmValue = 0;
    }
    void decodeInstruction(fetchStage &f);
    ~decodeStage(){};

public:
    uint16_t RDst, RSrc0_Value, RSrc1_Value, ImmValue, PC, PC_Offset;
    uint16_t functionalUnit;
};

void decodeStage::decodeInstruction(fetchStage &f)
{
    PC = f.PC;
    switch (f.insnCode & MASK_INSN)
    {
    case LDI:
        RDst = (f.insnCode & MASK_RDst) >> 4;
        ImmValue = (f.insnCode & MASK_LDImmValue) >> 8;
        functionalUnit = LOAD;
        break;

    case ADDI:
        RDst = (f.insnCode & MASK_RDst) >> 4;
        RSrc0_Value = registerFile[(f.insnCode & MASK_RSrc) >> 8];
        ImmValue = (f.insnCode & MASK_ADDImmValue) >> 12;
        functionalUnit = ALU;
        break;

    case BNE:
        RSrc0_Value = registerFile[(f.insnCode & MASK_RDst) >> 4];
        RSrc1_Value = registerFile[(f.insnCode & MASK_RSrc) >> 8];
        PC_Offset = (f.insnCode & MASK_BROffset) >> 12;
        functionalUnit = BR;

        break;
    case HLT:
        functionalUnit = HALT;
        break;
    default:
        cerr << "Unknown Instruction" << endl;
        exit(1);
    }
}
#endif