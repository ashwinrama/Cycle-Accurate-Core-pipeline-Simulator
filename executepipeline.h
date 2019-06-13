#ifndef EXECUTE_H
#define EXECUTE_H
#include "core_opcodes.h"
#include "decodepipeline.h"

class executeStage
{
public:
    executeStage(uint16_t initialPC)
    {
        cout << "Initializaing Execute" << endl;
        targetPC = initialPC;
        cycleCount = 0;
    }
    void executeInstruction(decodeStage &d);

    ~executeStage(){};
    uint16_t targetPC;

private:
    void printStats(const decodeStage &d) const;

    uint64_t cycleCount;
    const uint16_t pipelineCycles = 2;
    const uint16_t LDCycles = 1;
    const uint16_t ALUCycles = 5;
    const uint16_t BRCycles = 1;
    const uint16_t stallCycles = 2;
};

void executeStage::executeInstruction(decodeStage &d)
{
    printStats(d);

    switch (d.functionalUnit)
    {
    case LOAD:
        cout << "LD \t";

        d.registerFile[d.RDst] = d.ImmValue;
        targetPC = d.PC + 1;
        cycleCount += pipelineCycles + LDCycles;
        break;
    case ALU:
        cout << "ADD \t";
        d.registerFile[d.RDst] = d.RSrc0_Value + d.ImmValue;
        targetPC = d.PC + 1;
        cycleCount += pipelineCycles + ALUCycles;
        break;
    case BR:
        cout << " BR \t";

        if ((d.RSrc0_Value ^ d.RSrc1_Value) != 0)
        {
            targetPC = d.PC - d.PC_Offset;
            cycleCount += pipelineCycles + BRCycles + stallCycles;
        }
        else
        {
            targetPC = d.PC + 1;
            cycleCount += pipelineCycles + BRCycles;
        }
        break;

    case HALT:
        cycleCount += pipelineCycles + 1;
        cout << "Program encountered HLT at execute.\n End of Simulation" << endl;
        exit(0);
    default:
        cerr << "Unknown Instruction" << endl;
        exit(1);
    }
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
        cout << d.PC << '\t';
        cout << d.RDst << '\t';
        cout << d.RSrc0_Value << '\t' << '\t';
        cout << d.RSrc1_Value << '\t' << '\t';
        cout << d.ImmValue << '\t' << '\t';
        cout << targetPC << '\n';
    }
}
#endif