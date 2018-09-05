#include "pseudoinstruction.h"
#include "parser.h"
#include <vector>
#include <istream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <iostream>

using std::istream;
using std::string;
using std::runtime_error;
using std::exception;
using std::cout;

string toStr(int x) {
    string s = "";
    do {
        int c = x % 10;
        x /= 10;
        s = (char)(c + '0') + s;
    }
    while(x);
    return s;
}

class InvalidInstructionException : public exception {
public:
    InvalidInstructionException(int line) {
        message = "Invalid instruction on line: " + toStr(line);
    }

    virtual const char* what() const throw() {
        return message.c_str();
    }
private:
    string message;
};

bool Parser::read(istream& in) {
    if(in) {
        string s;
        getline(in,s);
        if(s == "")
            return 0;
        parseLine(s);
        in.clear();
    }
    return in;
}

void Parser::parseLine(string& str) {
    string copyStr = str;
    try {
        try {
            Pseudoinstruction psin = parseIns(str);
            parseComm(str);
            psins.push_back(psin);
        }
        catch(runtime_error e) {
            parseComm(str);
        }
    }
    catch(InvalidInstructionException e) {
        str = copyStr;
        parseSpaces(str);
        string s = parseStr(str);
        parseChr(str,':');
        if(labels.find(s) == labels.end())
            labels[s] = insNum;
        else
            throw runtime_error("Duplicate label on line: " + toStr(lineCount));
        Pseudoinstruction psin = parseIns(str);
        parseComm(str);
        psins.push_back(psin);
    }
}

Pseudoinstruction Parser::parseIns(string& str) {
    parseSpaces(str);
    string token = parseStr(str);
    if(token == "add") {
        Pseudoinstruction psins("add");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "addi") {
        Pseudoinstruction psins("addi");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "and") {
        Pseudoinstruction psins("and");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "andi") {
        Pseudoinstruction psins("andi");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "beq") {
        Pseudoinstruction psins("beq");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bgez") {
        Pseudoinstruction psins("bgez");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bgezal") {
        Pseudoinstruction psins("bgezal");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bgtz") {
        Pseudoinstruction psins("bgtz");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "blez") {
        Pseudoinstruction psins("blez");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bltz") {
        Pseudoinstruction psins("bltz");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bltzal") {
        Pseudoinstruction psins("bltzal");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bne") {
        Pseudoinstruction psins("bne");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "j") {
        Pseudoinstruction psins("j");
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "jal") {
        Pseudoinstruction psins("jal");
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "jr") {
        Pseudoinstruction psins("jr");
        parseReg(str,psins);
        return psins;
    }

    if(token == "lui") {
        Pseudoinstruction psins("lui");
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "lw") {
        Pseudoinstruction psins("lw");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            psins.args.push_back(0);
        }
        parseChr(str,'(');
        parseReg(str,psins);
        parseChr(str,')');
        return psins;
    }

    if(token == "nor") {
        Pseudoinstruction psins("nor");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "or") {
        Pseudoinstruction psins("or");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "ori") {
        Pseudoinstruction psins("ori");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "sll") {
        Pseudoinstruction psins("sll");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "sllv") {
        Pseudoinstruction psins("sllv");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "slt") {
        Pseudoinstruction psins("slt");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "sltu") {
        Pseudoinstruction psins("sltu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }


    if(token == "slti") {
        Pseudoinstruction psins("slti");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "sltiu") {
        Pseudoinstruction psins("sltiu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "sra") {
        Pseudoinstruction psins("sra");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "srav") {
        Pseudoinstruction psins("srav");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "srl") {
        Pseudoinstruction psins("srl");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }
    if(token == "srlv") {
        Pseudoinstruction psins("srlv");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "sub") {
        Pseudoinstruction psins("sub");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "sw") {
        Pseudoinstruction psins("sw");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            psins.args.push_back(0);
        }
        parseChr(str,'(');
        parseReg(str,psins);
        parseChr(str,')');
        return psins;
    }

    if(token == "xor") {
        Pseudoinstruction psins("xor");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "xori") {
        Pseudoinstruction psins("xori");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "abs") {
        Pseudoinstruction psins("abs");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 8;
        return psins;
    }

    if(token == "bal") {
        Pseudoinstruction psins("bal");
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bge") {
        Pseudoinstruction psins("bge");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bgeu") {
        Pseudoinstruction psins("bgeu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bgt") {
        Pseudoinstruction psins("bgt");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bgtu") {
        Pseudoinstruction psins("bgtu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "b") {
        Pseudoinstruction psins("b");
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "ble") {
        Pseudoinstruction psins("ble");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bleu") {
        Pseudoinstruction psins("bleu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "blt") {
        Pseudoinstruction psins("blt");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bltu") {
        Pseudoinstruction psins("bltu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        insNum += 4;
        return psins;
    }

    if(token == "bnez") {
        Pseudoinstruction psins("bnez");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "bz") {
        Pseudoinstruction psins("bz");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            parseLabel(str,psins);
        }
        return psins;
    }

    if(token == "clr") {
        Pseudoinstruction psins("clr");
        parseReg(str,psins);
        return psins;
    }

    if(token == "la") {
        Pseudoinstruction psins("la");
        parseReg(str,psins);
        parseChr(str,',');
        try {
            parseImm(str,psins);
        }
        catch(runtime_error e) {
            psins.args.push_back(0);
        }
        parseChr(str,'(');
        parseReg(str,psins);
        parseChr(str,')');
        if(psins.args[1] > 32767|| psins.args[1] < -32768)
            insNum += 8;
        return psins;
    }

    if(token == "li") {
        Pseudoinstruction psins("li");
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        if(psins.args[1] > 32767|| psins.args[1] < -32768)
            insNum += 4;
        return psins;
    }

    if(token == "halt") {
        Pseudoinstruction psins("halt");
        return psins;
    }

    if(token == "move") {
        Pseudoinstruction psins("move");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "neg") {
        Pseudoinstruction psins("neg");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "nop") {
        Pseudoinstruction psins("nop");
        insNum -= 4;
        return psins;
    }

    if(token == "not") {
        Pseudoinstruction psins("not");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }
    if(token == "seq") {
        Pseudoinstruction psins("seq");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 12;
        return psins;
    }

    if(token == "sge") {
        Pseudoinstruction psins("sge");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 4;
        return psins;
    }

    if(token == "sgeu") {
        Pseudoinstruction psins("sgeu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 4;
        return psins;
    }

    if(token == "sgt") {
        Pseudoinstruction psins("sgt");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "sgtu") {
        Pseudoinstruction psins("sgtu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        return psins;
    }

    if(token == "sleu") {
        Pseudoinstruction psins("sleu");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 4;
        return psins;
    }

    if(token == "sle") {
        Pseudoinstruction psins("sle");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 4;
        return psins;
    }

    if(token == "sne") {
        Pseudoinstruction psins("sne");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        insNum += 8;
        return psins;
    }

    if(token == "subi") {
        Pseudoinstruction psins("subi");
        parseReg(str,psins);
        parseChr(str,',');
        parseReg(str,psins);
        parseChr(str,',');
        parseImm(str,psins);
        return psins;
    }

    if(token == "break") {
        Pseudoinstruction psins("break");
        parseImm(str,psins);
        return psins;
    }

    throw InvalidInstructionException(lineCount);
}

void Parser::parseReg(string &str, Pseudoinstruction &psin) {
    parseSpaces(str);
    parseChr(str,'$');
    int x;
    try {
        x = parseInt(str);
    }
    catch(runtime_error e) {
        string s = parseStr(str);
        if(regsCode.find(s) != regsCode.end())
            x = regsCode[s];
        else
            throw runtime_error("Syntax error on line: " + toStr(lineCount));
    }
    psin.args.push_back(x);
}

void  Parser::parseImm(string &str, Pseudoinstruction &psin) {
    parseSpaces(str);
    int x = parseInt(str);
    psin.args.push_back(x);
}

void Parser::parseLabel(string &str, Pseudoinstruction &psin) {
    parseSpaces(str);
    psin.label = parseStr(str);
}

void Parser::parseChr(string &str, char ch) {
    char chara = str[0];
    if(str[0] == ch)
        str.erase(0,1);
    else
        throw runtime_error("Syntax error on line: " + toStr(lineCount));
}

void Parser::parseSpaces(string &str) {
    while(str.size() != 0 && (str[0] == ' ' || str[0] == '\t' || str[0] == '\r'))
        str.erase(0,1);
}

int Parser::parseInt(string &str) {
    int x = 0;
    if(!isdigit(str[0]))
        throw runtime_error("Syntax error on line: " + toStr(lineCount));
    while(str.size() != 0 && isdigit(str[0])) {
        x = x * 10 + (str[0] - '0');
        str.erase(0,1);
    }
    return x;
}

string Parser::parseStr(string &str) {
    string s = "";
    char chr = str[0];
    if(!isalpha(str[0]))
        throw runtime_error("Syntax error on line: " + toStr(lineCount));
    else
        s = s + str[0], str.erase(0,1);
    while(str.size() != 0 && isalnum(str[0])) {
        s = s + str[0];
        str.erase(0,1);
    }
    return s;
}

void Parser::parseComm(string& str) {
    parseSpaces(str);
    if(str != "") {
        parseChr(str,'-');
        parseChr(str,'-');
    }
}

void Parser::initRegsCode() {
    regsCode["zero"] = 0;
    regsCode["at"] = 1;
    regsCode["v0"] = 2;
    regsCode["v1"] = 3;
    regsCode["a0"] = 4;
    regsCode["a1"] = 5;
    regsCode["a2"] = 6;
    regsCode["a3"] = 7;
    regsCode["t0"] = 8;
    regsCode["t1"] = 9;
    regsCode["t2"] = 10;
    regsCode["t3"] = 11;
    regsCode["t4"] = 12;
    regsCode["t5"] = 13;
    regsCode["t6"] = 14;
    regsCode["t7"] = 15;
    regsCode["t8"] = 24;
    regsCode["t9"] = 25;
    regsCode["s0"] = 16;
    regsCode["s1"] = 17;
    regsCode["s2"] = 18;
    regsCode["s3"] = 19;
    regsCode["s4"] = 20;
    regsCode["s5"] = 21;
    regsCode["s6"] = 22;
    regsCode["s7"] = 23;
    regsCode["k0"] = 26;
    regsCode["k1"] = 27;
    regsCode["gp"] = 28;
    regsCode["sp"] = 29;
    regsCode["fp"] = 30;
    regsCode["ra"] = 31;
}
