#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "pseudoinstruction.h"
#include <vector>
#include <istream>
#include <map>
#include <exception>

class Parser {
public:
    Parser(std::istream& in) {
        if(!in.good())
            throw std::runtime_error("The file doesn't exists");
        initRegsCode();
        lineCount = 0;
        insNum = 0;
        while(read(in)) {
            lineCount++;
            insNum += 4;
        }
    }

    std::vector<Pseudoinstruction> psins;
    std::map<std::string,unsigned int> labels;
    std::map<std::string,int> regsCode;
private:
    unsigned int lineCount;
    unsigned int insNum;
    bool read (std::istream&);
    void parseLine(std::string&);
    Pseudoinstruction parseIns(std::string&);
    void parseReg(std::string&,Pseudoinstruction&);
    void parseImm(std::string&,Pseudoinstruction&);
    void parseLabel(std::string&,Pseudoinstruction&);
    void parseChr(std::string&,char);
    void parseSpaces(std::string&);
    int parseInt(std::string&);
    std::string parseStr(std::string&);
    void parseComm(std::string&);
    void initRegsCode();
};

#endif // PARSER_H_INCLUDED
