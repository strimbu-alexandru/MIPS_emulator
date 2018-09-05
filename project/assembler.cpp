#include "pseudoinstruction.h"
#include "instruction.h"
#include "assembler.h"
#include "parser.h"
#include <vector>
#include <string>
#include <map>
#include <exception>
#include <iostream>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::runtime_error;

Assembler::Assembler(vector<Pseudoinstruction> psins, std::map<std::string,unsigned int> labels) {
    try {
        lineCount = 0;
        for(vector<Pseudoinstruction>::iterator ii = psins.begin(); ii != psins.end(); ++ii, lineCount += 4) {
            printCount();
            if(ii->getType() == "add")
                assembleAdd(*ii);
            else
            if(ii->getType() == "addi")
                assembleAddi(*ii);
            else
            if(ii->getType() == "and")
                assembleAnd(*ii);
            else
            if(ii->getType() == "andi")
                assembleAndi(*ii);
            else
            if(ii->getType() == "beq")
                assembleBeq(*ii,labels);
            else
            if(ii->getType() == "bgez")
                assembleBgez(*ii,labels);
            else
            if(ii->getType() == "bgezal")
                assembleBgezal(*ii,labels);
            else
            if(ii->getType() == "bgtz")
                assembleBgtz(*ii,labels);
            else
            if(ii->getType() == "blez")
                assembleBlez(*ii,labels);
            else
            if(ii->getType() == "bltz")
                assembleBltz(*ii,labels);
            else
            if(ii->getType() == "bltzal")
                assembleBltzal(*ii,labels);
            else
            if(ii->getType() == "bne")
                assembleBne(*ii,labels);
            else
            if(ii->getType() == "j")
                assembleJ(*ii,labels);
            else
            if(ii->getType() == "jal")
                assembleJal(*ii,labels);
            else
            if(ii->getType() == "jr")
                assembleJr(*ii);
            else
            if(ii->getType() == "lui")
                assembleLui(*ii);
            else
            if(ii->getType() == "lw")
                assembleLw(*ii);
            else
            if(ii->getType() == "nor")
                assembleNor(*ii);
            else
            if(ii->getType() == "or")
                assembleOr(*ii);
            else
            if(ii->getType() == "ori")
                assembleOri(*ii);
            else
            if(ii->getType() == "sll")
                assembleSll(*ii);
            else
            if(ii->getType() == "sllv")
                assembleSllv(*ii);
            else
            if(ii->getType() == "slt")
                assembleSlt(*ii);
            else
            if(ii->getType() == "sltu")
                assembleSltu(*ii);
            else
            if(ii->getType() == "slti")
                assembleSlti(*ii);
            else
            if(ii->getType() == "sltiu")
                assembleSltiu(*ii);
            else
            if(ii->getType() == "sra")
                assembleSra(*ii);
            else
            if(ii->getType() == "srav")
                assembleSrav(*ii);
            else
            if(ii->getType() == "srl")
                assembleSrl(*ii);
            else
            if(ii->getType() == "srlv")
                assembleSrlv(*ii);
            else
            if(ii->getType() == "sub")
                assembleSub(*ii);
            else
            if(ii->getType() == "sw")
                assembleSw(*ii);
            else
            if(ii->getType() == "xor")
                assembleXor(*ii);
            else
            if(ii->getType() == "xori")
                assembleXori(*ii);
            else
            if(ii->getType() == "abs")
                assembleAbs(*ii);
            else
            if(ii->getType() == "bal")
                assembleBal(*ii,labels);
            else
            if(ii->getType() == "bge")
                assembleBge(*ii,labels);
            else
            if(ii->getType() == "bgt")
                assembleBgt(*ii,labels);
            else
            if(ii->getType() == "b")
                assembleB(*ii,labels);
            else
            if(ii->getType() == "ble")
                assembleBle(*ii,labels);
            else
            if(ii->getType() == "blt")
                assembleBlt(*ii,labels);
            else
            if(ii->getType() == "bnez")
                assembleBnez(*ii,labels);
            else
            if(ii->getType() == "bz")
                assembleBz(*ii,labels);
            else
            if(ii->getType() == "clr")
                assembleClr(*ii);
            else
            if(ii->getType() == "la")
                assembleLa(*ii);
            else
            if(ii->getType() == "li")
                assembleLi(*ii);
            else
            if(ii->getType() == "halt")
                assembleHalt();
            else
            if(ii->getType() == "move")
                assembleMove(*ii);
            else
            if(ii->getType() == "neg")
                assembleNeg(*ii);
            else
            if(ii->getType() == "nop")
                assembleNop();
            else
            if(ii->getType() == "not")
                assembleNot(*ii);
            else
            if(ii->getType() == "seq")
                assembleSeq(*ii);
            else
            if(ii->getType() == "sge")
                assembleSge(*ii);
            else
            if(ii->getType() == "sgt")
                assembleSgt(*ii);
            else
            if(ii->getType() == "sle")
                assembleSle(*ii);
            else
            if(ii->getType() == "sne")
                assembleSne(*ii);
            else
            if(ii->getType() == "subi")
                assembleSubi(*ii);
            else
            if(ii->getType() == "bgeu")
                assembleBgeu(*ii,labels);
            else
            if(ii->getType() == "bgtu")
                assembleBgtu(*ii,labels);
            else
            if(ii->getType() == "bleu")
                assembleBleu(*ii,labels);
            else
            if(ii->getType() == "bltu")
                assembleBltu(*ii,labels);
            else
            if(ii->getType() == "sgeu")
                assembleSgeu(*ii);
            else
            if(ii->getType() == "sgtu")
                assembleSgtu(*ii);
            else
            if(ii->getType() == "sleu")
                assembleSleu(*ii);
            else
            if(ii->getType() == "break")
                assembleBreak(*ii);
        }
    }
    catch(runtime_error e) {
        cerr << e.what() << endl;
    }
}

void Assembler::assembleAdd(Pseudoinstruction psin) {
    Instruction *in = new Add(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleAddi(Pseudoinstruction psin) {
    Instruction *in = new Addi(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleAnd(Pseudoinstruction psin) {
    Instruction *in = new And(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleAndi(Pseudoinstruction psin) {
    Instruction *in = new Andi(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBeq(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Beq(psin.args[0],psin.args[1],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgez(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bgez(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgezal(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bgezal(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgtz(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bgtz(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBlez(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Blez(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBltz(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bltz(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBltzal(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bltzal(psin.args[0],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBne(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bne(psin.args[0],psin.args[1],computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleJ(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new J(labels[psin.label]/4);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleJal(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Jal(labels[psin.label]/4);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleJr(Pseudoinstruction psin) {
    Instruction *in = new Jr(psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleLui(Pseudoinstruction psin) {
    Instruction *in = new Lui(psin.args[0],psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleLw(Pseudoinstruction psin) {
    Instruction *in = new Lw(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleNor(Pseudoinstruction psin) {
    Instruction *in = new Nor(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleOr(Pseudoinstruction psin) {
    Instruction *in = new Or(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleOri(Pseudoinstruction psin) {
    Instruction *in = new Ori(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSll(Pseudoinstruction psin) {
    Instruction *in = new Sll(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSllv(Pseudoinstruction psin) {
    Instruction *in = new Sllv(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSlt(Pseudoinstruction psin) {
    Instruction *in = new Slt(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSlti(Pseudoinstruction psin) {
    Instruction *in = new Slti(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSra(Pseudoinstruction psin) {
    Instruction *in = new Sra(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSrav(Pseudoinstruction psin) {
    Instruction *in = new Srav(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSrl(Pseudoinstruction psin) {
    Instruction *in = new Srl(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSrlv(Pseudoinstruction psin) {
    Instruction *in = new Srlv(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSub(Pseudoinstruction psin) {
    Instruction *in = new Sub(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSw(Pseudoinstruction psin) {
    Instruction *in = new Sw(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleXor(Pseudoinstruction psin) {
    Instruction *in = new Xor(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleXori(Pseudoinstruction psin) {
    Instruction *in = new Xori(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSltiu(Pseudoinstruction psin) {
    Instruction *in = new Sltiu(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSltu(Pseudoinstruction psin) {
    Instruction *in = new Sltu(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBreak(Pseudoinstruction psin) {
    Instruction *in = new Break(psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleAbs(Pseudoinstruction psin) {
    Instruction *in = new Add(psin.args[0],psin.args[1],0);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Bgez(psin.args[1],1);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Sub(psin.args[0],0,psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBal(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bgezal(0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBge(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Slt(1,psin.args[0],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgeu(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Sltu(1,psin.args[0],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgt(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Slt(1,psin.args[1],psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Bne(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBgtu(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Sltu(1,psin.args[1],psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Bne(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleB(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Beq(0,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBle(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Slt(1,psin.args[1],psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBleu(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Sltu(1,psin.args[1],psin.args[0]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBlt(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Slt(1,psin.args[0],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Bne(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBltu(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Sltu(1,psin.args[0],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Bne(1,0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBnez(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Bne(psin.args[0],0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleBz(Pseudoinstruction psin, map<string,unsigned int> labels) {
    Instruction *in = new Beq(psin.args[0],0,computeDist(psin.label,labels));
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleClr(Pseudoinstruction psin) {
    Instruction *in = new Add(psin.args[0],0,0);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleLa(Pseudoinstruction psin) {
    if(psin.args[1] > 32767|| psin.args[1] < -32768) {
        Instruction *in = new Lui(1,psin.args[1]>>16);
        ins.push_back(in);
        in->print();cout << endl;
        lineCount += 4;
        printCount();
        in = new Addi(1,1,psin.args[1]&0xFFFF);
        ins.push_back(in);
        in->print();cout << endl;
        lineCount += 4;
        printCount();
        in = new Add(psin.args[0],psin.args[1],1);
        ins.push_back(in);
        in->print();cout << endl;
    }
    else {
        Instruction *in = new Addi(psin.args[0],psin.args[2],psin.args[1]);
        ins.push_back(in);
        in->print();cout << endl;
    }

}

void Assembler::assembleLi(Pseudoinstruction psin) {
    if(psin.args[1] > 32767 || psin.args[1] < -32768) {
        Instruction *in = new Lui(psin.args[0],(psin.args[1]>>16) + 1);
        ins.push_back(in);
        in->print();cout << endl;
        lineCount += 4;
        printCount();
        in = new Addi(psin.args[0],psin.args[0],psin.args[1]&0xFFFF);
        ins.push_back(in);
        in->print();cout << endl;
    }
    else {
        Instruction *in = new Addi(psin.args[0],0,psin.args[1]);
        ins.push_back(in);
        in->print();cout << endl;
    }
}

void Assembler::assembleHalt() {
    Instruction *in = new Break(0);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleMove(Pseudoinstruction psin) {
    Instruction *in = new Add(psin.args[0],psin.args[1],0);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleNeg(Pseudoinstruction psin) {
    Instruction *in = new Sub(psin.args[0],0,psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleNop() {
    Instruction *in = new Sll(0,0,0);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleNot(Pseudoinstruction psin) {
    Instruction *in = new Nor(psin.args[0],psin.args[1],0);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSeq(Pseudoinstruction psin) {
    Instruction *in = new Sub(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(psin.args[0],0,1);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Addi(psin.args[0],0,1);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Xori(psin.args[0],psin.args[0],1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSge(Pseudoinstruction psin) {
    Instruction *in = new Slt(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Xori(psin.args[0],psin.args[0],1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSgeu(Pseudoinstruction psin) {
    Instruction *in = new Sltu(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Xori(psin.args[0],psin.args[0],1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSgt(Pseudoinstruction psin) {
    Instruction *in = new Slt(psin.args[0],psin.args[2],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSgtu(Pseudoinstruction psin) {
    Instruction *in = new Sltu(psin.args[0],psin.args[2],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSle(Pseudoinstruction psin) {
    Instruction *in = new Slt(psin.args[0],psin.args[2],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Xori(psin.args[0],psin.args[0],1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSleu(Pseudoinstruction psin) {
    Instruction *in = new Sltu(psin.args[0],psin.args[2],psin.args[1]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Xori(psin.args[0],psin.args[0],1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSne(Pseudoinstruction psin) {
    Instruction *in = new Sub(psin.args[0],psin.args[1],psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Beq(psin.args[0],0,1);
    ins.push_back(in);
    in->print();cout << endl;
    lineCount += 4;
    printCount();
    in = new Addi(psin.args[0],0,1);
    ins.push_back(in);
    in->print();cout << endl;
}

void Assembler::assembleSubi(Pseudoinstruction psin) {
    Instruction *in = new Addi(psin.args[0],psin.args[1],-psin.args[2]);
    ins.push_back(in);
    in->print();cout << endl;
}

int Assembler::numDigits(int n) {
    int x = 0;
    do {
        x++;
        n /= 10;
    }
    while(n);
    return x;
}

void Assembler::printCount() {
    cout << "L" << lineCount << ":" << string(8 - numDigits(lineCount),' ');
}



int Assembler::computeDist(string label, map<string,unsigned int> labels) {
    return (labels[label] - lineCount) / 4 - 1;
}
