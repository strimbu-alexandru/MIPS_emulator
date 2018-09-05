#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include <vector>
#include "instruction.h"

class Processor {
public:
    int regs[32];
    int memory[8192];
    int pc;
    std::vector<Instruction*> ins;
    Processor(std::vector<Instruction*> ins) {
        this->ins = ins;
        pc = 0;
    }
    void executeInstructions();
private:
    void printRegs();
    int numDigits(int);
    void pause();
};

#endif // PROCESSOR_H_INCLUDED
