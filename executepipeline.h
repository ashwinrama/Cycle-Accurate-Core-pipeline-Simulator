#ifndef EXECUTE_H
#define EXECUTE_H
#include "core_opcodes.h"
#include "decodepipeline.h"
class decodeStage;

typedef struct {
    uint16_t targetPC = 0;
    bool stall=0;
    bool NOP = 0;
} executeRegister;

class executeStage
{
public:
    executeRegister *currentRegister_ptr, *nextRegister_ptr;

    executeStage(void);
    uint64_t cycleCount;
    void executeInstruction(decodeStage &d, bool);
    void updatePipelineRegs(bool, bool);

    ~executeStage(){};

private:
    void printStats(const decodeStage &d) const;
    executeRegister pipeReg0, pipeReg1;
    
    uint16_t eu_cycles;
    uint64_t insnCount;
    uint16_t pipelineCycles = NUM_PIPE_STAGES - 1;
    //Execution Unit Cycles
    const uint16_t LDCycles = 1;
    const uint16_t ALUCycles = 5;
    const uint16_t BRCycles = 1;
    const uint16_t stallCycles = NUM_PIPE_STAGES - 1;
};


#endif