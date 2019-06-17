#include "executepipeline.h"


executeStage::executeStage(void){

        cout << "Initializaing Execute" << endl;
        currentRegister_ptr = &pipeReg0;
        nextRegister_ptr = &pipeReg1;
        
        insnCount = 0;
}

void executeStage::executeInstruction(decodeStage &d, bool clk)
{
    printStats(d);

    if (this->currentRegister_ptr->NOP || d.currentRegister_ptr->functionalUnit==NOP) {
        //Insert NOPeu_cycleseu_cycles
        cout << "NOP \t";
        d.registerFile[0]= 0;  //R0 to 0; NOP execution like in RISC-V
        currentRegister_ptr->NOP = 0;

        eu_cycles = 1;
    }
    else {
        switch (d.currentRegister_ptr->functionalUnit)
        {
            case LOAD:

                cout << "LD \t";
                //New invokation of this EU
                if (currentRegister_ptr->stall == false) {
                    //Number of executed/completed insns.
                    insnCount++;
                    d.registerFile[d.currentRegister_ptr->RDst] = d.currentRegister_ptr->ImmValue; 
                    eu_cycles = LDCycles;
                }
                break;

            case ALU:
                cout << "ADD \t";
                //New invokation of this EU
                if (currentRegister_ptr->stall == false){
                    insnCount++;
                    d.registerFile[d.currentRegister_ptr->RDst] = d.currentRegister_ptr->RSrc0_Value + d.currentRegister_ptr->ImmValue;
                    eu_cycles = ALUCycles;
                }
                break;

            case BR:
                cout << " BR \t";
                if (currentRegister_ptr->stall == false) {
                    insnCount++;
                    if ((d.currentRegister_ptr->RSrc0_Value ^ d.currentRegister_ptr->RSrc1_Value) != 0)
                    {
                        nextRegister_ptr->targetPC = d.currentRegister_ptr->PC   - d.currentRegister_ptr->PC_Offset;
                        nextRegister_ptr->NOP = 1;
                    }
                    else
                    {
                        nextRegister_ptr->NOP = 0;
                    }
                    //New invokation of this EU
                    eu_cycles = BRCycles;
                }
                break;

            case HALT:
                cout << "HLT" << '\t';
                insnCount++;
                //Display Stats
                printStats(d);
                cout << "\nIPC: Number of Instructions/Cycle Count = " << insnCount << "/" << cycleCount << "=" << (insnCount / static_cast<float>(cycleCount)) << endl;
                cout << "Program encountered HLT at execute.\nEnd of Simulation" << endl;
                exit(0);

            default:
                cerr << "\nNOP " << '\t';
                break;
        }
    }

   //Stall pipeline, if number eu cycles is more than 1.
    if (eu_cycles > 1) {
        nextRegister_ptr->stall = 1;
        eu_cycles--;
    } else 
        nextRegister_ptr->stall = 0;

cycleCount++;
}

void executeStage::printStats(const decodeStage &d) const
{
    static bool headerPrint = 0;
    if (headerPrint == 0)
    {
        cout << "EU  Cycles\t PC\t RDst\t Rsrc0_Value\t Rsrc1_Value\t ImmValue\t NextPC\n";
        headerPrint = 1;
    }
    else
    {
        cout << cycleCount << '\t';
        cout << d.currentRegister_ptr->PC << '\t';
        cout << d.currentRegister_ptr->RDst << '\t';
        cout << d.currentRegister_ptr->RSrc0_Value << '\t' << '\t';
        cout << d.currentRegister_ptr->RSrc1_Value << '\t' << '\t';
        cout << d.currentRegister_ptr->ImmValue << '\t' << '\t';
        cout << currentRegister_ptr->targetPC << '\n';
    }
}

void executeStage::updatePipelineRegs(bool clk, bool stall){

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