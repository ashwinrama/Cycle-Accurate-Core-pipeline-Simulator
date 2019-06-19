#include <iostream>
#include <fstream>
#include "core_opcodes.h"
#include "fetchpipeline.h"
#include "decodepipeline.h"
#include "executepipeline.h"

using namespace std;
void writeProgram(void);

int main(void)
{
    //initialize
    uint16_t initialPC = 0;
    //static uint64_t cycleCount =0;

    fetchStage f(initialPC);
    decodeStage d;
    executeStage e;
    //---------------------------------------
    writeProgram();
    //---Performance Simulation--------------
    bool clk = 0;
    while (1)
    {
        f.fetchInstruction(e);
        d.decodeInstruction(f, e);
        e.executeInstruction(d);
        //----Update next clock registers
        e.updatePipelineRegs(0);
        //add more pipelines if needed for experimentation.
        d.updatePipelineRegs(e.currentRegister_ptr->stall);
        f.updatePipelineRegs(e.currentRegister_ptr->stall);
        
    }

    //system("pause");
    return 0;
}

void writeProgram(void)
{
    fstream programCode;
    programCode.open("./programASM.txt", ios::out);
    if (programCode.is_open())
    {
        //LDI R1, #0
        programCode << (0 << 8 | R1 << 4 | LDI) << '\n';
        //LDI R2, #20
        programCode << (20 << 8 | R2 << 4 | LDI) << '\n';
        //ADDI R1, #4
        programCode << (4 << 12 | R1 << 8 | R1 << 4 | ADDI) << '\n';
        //BNE R1, R2, #offset  (where, target_address = #PC - #offset)
        programCode << (1 << 12 | R2 << 8 | R1 << 4 | BNE) << '\n';
        //HLT
        programCode << (HLT) << '\n';
         //ADDI R0, #0/NOP
        programCode << (0 << 12 | R0 << 8 | R0 << 4 | ADDI) << '\n';
        programCode.close();
    }
}


