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
    fetchStage f;
    decodeStage d;
    executeStage e(initialPC);
    //---------------------------------------
    writeProgram();
    //---Performance Simulation--------------
    while (1)
    {
        f.fetchInstruction(e.targetPC);
        d.decodeInstruction(f);
        e.executeInstruction(d);
    }

    cout << "end of simulation" << endl;
    //system("pause");
    return 0;
}

void writeProgram(void)
{
    fstream programCode;
    programCode.open("./programASM.txt", ios::out);
    if (programCode.is_open())
    {
        //LDI R1, #4
        programCode << (4 << 8 | R1 << 4 | LDI) << '\n';
        //LDI R2, #20
        programCode << (20 << 8 | R2 << 4 | LDI) << '\n';
        //ADDI R1, #4
        programCode << (4 << 12 | R1 << 8 | R1 << 4 | ADDI) << '\n';
        //BNE R1, R2, #offset  (where, target_address = #PC - #offset)
        programCode << (1 << 12 | R2 << 8 | R1 << 4 | BNE) << '\n';
        programCode << (HLT) << '\n';
        programCode.close();
    }
}
