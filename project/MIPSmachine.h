#ifndef MIPSMACHINE_H_INCLUDED
#define MIPSMACHINE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>

class MIPSmachine {
public:
    MIPSmachine() { }
    void Start() {
        std::string s;
        std::cout << "Source file: ";
        getline(std::cin,s);
        std::cout << s << std::endl;
        std::ifstream fin (s.c_str());
        try {
            Parser p(fin);   //parse the input
            Assembler assmbl(p.psins,p.labels);   //assemble the instructions
            Processor proc(assmbl.ins);    //create the "processor"
            system("pause");
            proc.executeInstructions();     //processor executes the instructions
        }
        catch(std::runtime_error e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif // MIPSMACHINE_H_INCLUDED
