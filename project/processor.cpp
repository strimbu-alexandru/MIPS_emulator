#include <vector>
#include <iostream>
#include <cstdlib>
#include "instruction.h"
#include "processor.h"

using std::vector;
using std::cout;
using std::string;
using std::endl;

void Processor::executeInstructions() {
    pc = 0;
    int halt = 0;
    while(halt != 2){
        cout << 4*pc << ":" << string(8 - numDigits(4*pc),' ');
        Instruction* in = ins[pc];
        in->print();
        printRegs();
        in->execute(regs,memory,pc,halt);
        cout << endl;
        if(halt == 1)
            system("pause");
        ++pc;
    }
}

int Processor::numDigits(int n) {
    int x = 0;
    do {
        x++;
        n /= 10;
    }
    while(n);
    return x;
}

void Processor::printRegs() {
    cout << "    [" << regs[1];
    for(int i = 2;i <= 31; ++i)
        cout << "," << regs[i];
    cout <<"]";
}
