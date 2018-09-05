#include <iostream>
#include <fstream>
#include <cstdlib>
#include "parser.h"
#include "instruction.h"
#include "assembler.h"
#include "processor.h"
#include "MIPSmachine.h"


using std::cin;
using std::cout;
using std::vector;
using std::ifstream;
using std::endl;
using std::map;
using std::string;
using std::exception;
using std::runtime_error;
using std::cerr;

int main()
{
    MIPSmachine mach;
    mach.Start();
    return 0;
}
