#include "decodepipeline.h"

decodeStage::decodeStage(void) {
    
    cout << "Initializing decode" << endl;
    for (int i = 0; i < 4; i++)
    {
        registerFile[i] = 0;
    }
    currentRegister_ptr = &pipeReg0;
    nextRegister_ptr = &pipeReg1;

}

void decodeStage::decodeInstruction(fetchStage &f, executeStage &e) {
    if (e.currentRegister_ptr->NOP) {
        //Insert NOP
        nextRegister_ptr->functionalUnit = NOP;
        nextRegister_ptr->RDst = 0;
        nextRegister_ptr->RSrc0_Value = 0;
        nextRegister_ptr->RSrc1_Value = 0;
        nextRegister_ptr->ImmValue = 0;
    }
    else {
        nextRegister_ptr->PC = f.currentRegister_ptr->PC;

        switch (f.currentRegister_ptr->insnCode & MASK_INSN)
        {
        case LDI:
            nextRegister_ptr->RDst = (f.currentRegister_ptr->insnCode & MASK_RDst) >> 4;
            nextRegister_ptr->ImmValue = (f.currentRegister_ptr->insnCode & MASK_LDImmValue) >> 8;
            nextRegister_ptr->functionalUnit = LOAD;
            break;

        case ADDI:
            nextRegister_ptr->RDst = (f.currentRegister_ptr->insnCode & MASK_RDst) >> 4;
            nextRegister_ptr->RSrc0_Value = registerFile[(f.currentRegister_ptr->insnCode & MASK_RSrc) >> 8];
            nextRegister_ptr->ImmValue = (f.currentRegister_ptr->insnCode & MASK_ADDImmValue) >> 12;
            nextRegister_ptr->functionalUnit = ALU;
            break;

        case BNE:
            nextRegister_ptr->RSrc0_Value = registerFile[(f.currentRegister_ptr->insnCode & MASK_RDst) >> 4];
            nextRegister_ptr->RSrc1_Value = registerFile[(f.currentRegister_ptr->insnCode & MASK_RSrc) >> 8];
            nextRegister_ptr->PC_Offset = (f.currentRegister_ptr->insnCode & MASK_BROffset) >> 12;
            nextRegister_ptr->functionalUnit = BR;

            break;
        case HLT:
            nextRegister_ptr->functionalUnit = HALT;
            break;
        default:
            //cerr << "\nUnknown/NOP Instruction" << endl;
            break;
        }
    }
}


void decodeStage::updatePipelineRegs(bool stall){

  if (!stall){
    if (clk == 0){
        currentRegister_ptr = &pipeReg0;
        nextRegister_ptr = &pipeReg1;
    } else {
        currentRegister_ptr = &pipeReg1;
        nextRegister_ptr = &pipeReg0;
    }
    clk =!clk;
  }
}