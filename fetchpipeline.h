#ifndef FETCH_H
#define FETCH_H
#include "core_opcodes.h"
#include "executepipeline.h"

#include <vector>
class executeStage;
class decodeStage;

typedef struct {
    uint16_t insnCode;
    uint16_t PC;
    uint16_t nextPC;
} fetchRegister;

class fetchStage
{
public:
    fetchRegister *currentRegister_ptr, *nextRegister_ptr;
    fetchStage(uint16_t initialPC);
    void fetchInstruction(executeStage &e, bool clk);
    void updatePipelineRegs(bool, bool);

    ~fetchStage(){};

private:
    fetchRegister pipeReg0, pipeReg1;
    //uint16_t insnCode, PC;
    fstream programCode;
    vector<uint16_t> insnCache;

};

#endif