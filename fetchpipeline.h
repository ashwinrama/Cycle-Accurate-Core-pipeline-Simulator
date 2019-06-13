#ifndef FETCH_H
#define FETCH_H
#include "core_opcodes.h"
#include <vector>

class fetchStage
{
public:
    uint16_t insnCode, PC;
    fetchStage(void);
    void fetchInstruction(uint16_t target_pc);
    ~fetchStage(){};

private:
    fstream programCode;
    vector<uint16_t> insnCache;
};

fetchStage::fetchStage(void)
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
}

void fetchStage::fetchInstruction(uint16_t targetPC)
{
    insnCode = insnCache[targetPC];
    PC = targetPC;
}
#endif