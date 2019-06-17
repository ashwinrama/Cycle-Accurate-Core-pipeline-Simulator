
#include "fetchpipeline.h"

fetchStage::fetchStage(uint16_t initialPC)
{
    uint16_t insn;
    cout << "Initializing fetch" << endl;

    programCode.open("./programASM.txt", ios::in);
    if (programCode.is_open())
    {
        while (programCode >> insn)
        {
            insnCache.push_back(insn);
        }
    }
    programCode.close();

    pipeReg0.nextPC = initialPC;
    pipeReg1.nextPC = initialPC;
    currentRegister_ptr = &pipeReg0;
    nextRegister_ptr = &pipeReg1;
}

void fetchStage::fetchInstruction(executeStage &e, bool clk)
{
    if (!e.currentRegister_ptr->NOP) {
        nextRegister_ptr->insnCode = insnCache[currentRegister_ptr->nextPC];
        nextRegister_ptr->PC = currentRegister_ptr->nextPC;
        nextRegister_ptr->nextPC =  currentRegister_ptr->nextPC + 1;
    }
    else { //Use jmp PC
        nextRegister_ptr->insnCode = insnCache[e.currentRegister_ptr->targetPC];
        nextRegister_ptr->PC = e.currentRegister_ptr->targetPC;
        nextRegister_ptr->nextPC =   e.currentRegister_ptr->targetPC + 1;
    }

}

void fetchStage::updatePipelineRegs(bool clk, bool stall){

  if (!stall){
    if (clk == 0){
        currentRegister_ptr = &pipeReg0;
        nextRegister_ptr = &pipeReg1;
        } else {
        currentRegister_ptr = &pipeReg1;
        nextRegister_ptr = &pipeReg0;
        }
  }
}
