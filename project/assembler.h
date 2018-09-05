#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "pseudoinstruction.h"
#include "instruction.h"
#include <vector>
#include <map>

class Assembler {
public:
    std::vector<Instruction*> ins;
    Assembler(std::vector<Pseudoinstruction> psins, std::map<std::string,unsigned int> labels);
private:
    unsigned int lineCount;
    void assembleAdd(Pseudoinstruction psin);
    void assembleAddi(Pseudoinstruction psin);
    void assembleAnd(Pseudoinstruction psin);
    void assembleAndi(Pseudoinstruction psin);
    void assembleBeq(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBgez(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBgezal(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBgtz(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBlez(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBltz(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBltzal(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBne(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleJ(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleJal(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleJr(Pseudoinstruction psin);
    void assembleLui(Pseudoinstruction psin);
    void assembleLw(Pseudoinstruction psin);
    void assembleNor(Pseudoinstruction psin);
    void assembleOr(Pseudoinstruction psin);
    void assembleOri(Pseudoinstruction psin);
    void assembleSll(Pseudoinstruction psin);
    void assembleSllv(Pseudoinstruction psin);
    void assembleSlt(Pseudoinstruction psin);
    void assembleSltu(Pseudoinstruction psin);
    void assembleSlti(Pseudoinstruction psin);
    void assembleSltiu(Pseudoinstruction psin);
    void assembleSra(Pseudoinstruction psin);
    void assembleSrav(Pseudoinstruction psin);
    void assembleSrl(Pseudoinstruction psin);
    void assembleSrlv(Pseudoinstruction psin);
    void assembleSub(Pseudoinstruction psin);
    void assembleSw(Pseudoinstruction psin);
    void assembleXor(Pseudoinstruction psin);
    void assembleXori(Pseudoinstruction psin);
    void assembleAbs(Pseudoinstruction psin);
    void assembleBal(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBge(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBgt(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleB(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBle(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBlt(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBnez(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBz(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleClr(Pseudoinstruction psin);
    void assembleLa(Pseudoinstruction psin);
    void assembleLi(Pseudoinstruction psin);
    void assembleHalt();
    void assembleMove(Pseudoinstruction psin);
    void assembleNeg(Pseudoinstruction psin);
    void assembleNop();
    void assembleNot(Pseudoinstruction psin);
    void assembleSeq(Pseudoinstruction psin);
    void assembleSge(Pseudoinstruction psin);
    void assembleSgt(Pseudoinstruction psin);
    void assembleSle(Pseudoinstruction psin);
    void assembleSne(Pseudoinstruction psin);
    void assembleSubi(Pseudoinstruction psin);
    void assembleBgeu(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBgtu(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBleu(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleBltu(Pseudoinstruction psin, std::map<std::string,unsigned int> labels);
    void assembleSgeu(Pseudoinstruction psin);
    void assembleSgtu(Pseudoinstruction psin);
    void assembleSleu(Pseudoinstruction psin);
    void assembleBreak(Pseudoinstruction psin);
    int computeDist(std::string, std::map<std::string,unsigned int>);
    void printCount();
    int numDigits(int);
};

#endif // ASSEMBLER_H_INCLUDED
