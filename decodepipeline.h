#ifndef DECODE_H
#define DECODE_H
#include "fetchpipeline.h"
#include "core_opcodes.h"
class fetchStage;
class executeStage;

typedef struct {
    uint16_t RDst=0, RSrc0_Value=0, RSrc1_Value=0, ImmValue=0, PC=0, PC_Offset=0;
    uint16_t functionalUnit = 0;
} decodeRegister;


class decodeStage
{
public:
    uint16_t registerFile[4];
    decodeRegister *currentRegister_ptr, *nextRegister_ptr;

    decodeStage(void);
    void updatePipelineRegs( bool);

    void decodeInstruction(fetchStage &f, executeStage &e);
    ~decodeStage(){};

private:
    decodeRegister pipeReg0, pipeReg1;
    bool clk = 1;
};

#endif