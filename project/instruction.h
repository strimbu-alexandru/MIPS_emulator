#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#define bias 4096

#include <iostream>

//Definitions of instructions

class Instruction {
public:
    Instruction() { }
    virtual void print() { }
    virtual void execute(int[],int[],int&,int&) { }
};

class RType : public Instruction {
public:
    short rd,rs,rt;
    RType(short rd, short rs, short rt) {
        this->rd = rd;
        this->rs = rs;
        this->rt = rt;
    }
};

class IType : public Instruction {
public:
    short rt,rs,n;
    IType(short rt, short rs, short n) {
        this->rt = rt;
        this->rs = rs;
        this->n = n;
    }
};

class JType : public Instruction {
public:
    unsigned int n;
    JType(unsigned int n) {
        this->n = n;
    }
};

class Add : public RType {
public:
    Add(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "add " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(rd)
            regs[rd] = regs[rs] + regs[rt];
    }
};

class Addi : public IType {
public:
    Addi(short rt, short rs, short n) : IType(rt,rs,n) { }
    virtual void print() {
        std::cout << "addi " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(rt)
            regs[rt] = regs[rs] + n;
    }
};

class And : public RType {
public:
    And(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "and " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(rd)
            regs[rd] = regs[rs] & regs[rt];
    }
};

class Andi : public IType {
public:
    Andi(short rt, short rs, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "andi " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(rt)
            regs[rt] = regs[rs] & n;
    }
};

class Beq : public IType {
public:
    Beq(short rs, short rt, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "beq " << "$" << rs << ", $" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] == regs[rt])
            pc = pc + n;
    }
};

class Bgez : public IType {
public:
    Bgez(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "bgez " << "$" << rs << ", " << n ;
    }

    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] >= 0)
            pc = pc + n;
    }
};

class Bgezal : public IType {
public:
    Bgezal(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "bgezal " << "$" << rs << ", " << n ;
    }

    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] >= 0) {
            regs[31] = 4 * pc + 4;
            pc = pc + n;
        }
    }
};

class Bgtz : public IType {
public:
    Bgtz(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "bgtz " << "$" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] > 0)
            pc = pc + n;
    }
};

class Blez : public IType {
public:
    Blez(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "blez " << "$" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] <= 0)
            pc = pc + n;
    }
};

class Bltz : public IType {
public:
    Bltz(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "bltz " << "$" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] < 0)
            pc = pc + n;
    }
};

class Bltzal : public IType {
public:
    Bltzal(short rs, short n) : IType(-1,rs,n) { }
    void print() {
        std::cout << "bltzal " << "$" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] < 0) {
            regs[31] = 4 * pc + 4;
            pc = pc + n;
        }
    }
};

class Bne : public IType {
public:
    Bne(short rs, short rt, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "bne " << "$" << rs << ", $" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] != regs[rt])
            pc = pc + n;
    }
};

class J : public JType {
public:
    J(unsigned int n) : JType(n) { }
    void print() {
        std::cout << "j " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        pc = n - 1;
    }
};

class Jal : public JType {
public:
    Jal(unsigned int n) : JType(n) { }
    void print() {
        std::cout << "jal " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[31] = 4 * pc + 4;
        pc = n - 1;
    }
};

class Jr : public RType {
public:
    Jr(short rs) : RType(-1,rs,-1) { }
    void print() {
        std::cout << "jr " << "$" << rs ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        pc = regs[31]/4 - 1;
    }
};

class Lui : public IType {
public:
    Lui(short rt, short n) : IType(rt,-1,n) { }
    void print() {
        std::cout << "lui " << "$" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rt] = n << 16;
    }
};

class Lw : public IType {
public:
    Lw(short rt, short n, short rs) : IType(rt,rs,n) { }
    void print() {
        std::cout << "lw " << "$" << rt << ", " << n << "($" << rs << ")" ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rt] = memory[regs[rs]/4 + n/4 + bias];
    }
};

class Nor : public RType {
public:
    Nor(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "nor " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = ~(regs[rs] | regs[rt]);
    }
};

class Or : public RType {
public:
    Or(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "or " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = regs[rs] | regs[rt];
    }
};

class Ori : public IType {
public:
    Ori(short rt, short rs, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "ori " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rt] = regs[rs] | n;
    }
};

class Sll : public IType {
public:
    Sll(short rs, short rt, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "sll " << "$" << rs << ", $" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rs] = regs[rt] << n;
    }
};

class Sllv : public RType {
public:
    Sllv(short rd, short rt, short rs) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "sllv " << "$" << rd << ", $" << rt << ", $" << rs ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = regs[rt] << regs[rs];
    }
};

class Slt : public RType {
public:
    Slt(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "slt " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] < regs[rt])
            regs[rd] = 1;
        else
            regs[rd] = 0;
    }
};

class Sltu : public RType {
public:
    Sltu(unsigned short rd,unsigned short rs,unsigned short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "sltu " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if((unsigned)regs[rs] < (unsigned)regs[rt])
            regs[rd] = 1;
        else
            regs[rd] = 0;
    }
};

class Slti : public IType {
public:
    Slti(short rt, short rs, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "slti " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(regs[rs] < n)
            regs[rt] = 1;
        else
            regs[rt] = 0;
    }
};

class Sltiu : public IType {
public:
    Sltiu(unsigned short rt,unsigned short rs,unsigned short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "sltiu " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if((unsigned)regs[rs] < (unsigned)n)
            regs[rt] = 1;
        else
            regs[rt] = 0;
    }
};

class Sra : public IType {
public:
    Sra(short rs, short rt, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "sra " << "$" << rs << ", $" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        int x = 1 << n;
        regs[rs] = regs[rt] / x;
    }
};

class Srav : public RType {
public:
    Srav(short rd, short rt, short rs) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "srav " << "$" << rd << ", $" << rt << ", $" << rs ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        int x = 1 << regs[rs];
        regs[rd] = regs[rt] / x;
    }
};

class Srl : public IType {
public:
    Srl(short rs, short rt, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "srl " << "$" << rs << ", $" << rt << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rs] = regs[rt] >> n;
    }
};

class Srlv : public RType {
public:
    Srlv(short rd, short rt, short rs) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "srlv " << "$" << rd << ", $" << rt << ", $" << rs ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = regs[rt] >> regs[rs];
    }
};

class Sub : public RType {
public:
    Sub(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "sub " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = regs[rs] - regs[rt];
    }
};

class Sw : public IType {
public:
    Sw(short rt, short n, short rs) : IType(rt,rs,n) { }
    void print() {
        std::cout << "sw " << "$" << rt << ", " << n << "($" << rs << ")" ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        memory[regs[rs]/4 + n/4 + bias] = regs[rt];
    }
};

class Xor : public RType {
public:
    Xor(short rd, short rs, short rt) : RType(rd,rs,rt) { }
    void print() {
        std::cout << "xor " << "$" << rd << ", $" << rs << ", $" << rt ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rd] = regs[rs] ^ regs[rt];
    }
};

class Xori : public IType {
public:
    Xori(short rt, short rs, short n) : IType(rt,rs,n) { }
    void print() {
        std::cout << "xori " << "$" << rt << ", $" << rs << ", " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        regs[rt] = regs[rs] ^ n;
    }
};

class Break : public IType {
public:
    Break(short n) : IType(-1,-1,n) { }
    void print() {
        std::cout << "break " << n ;
    }
    void execute(int regs[],int memory[],int &pc,int &halt) {
        if(n == 0)
            halt = 2;
        else
            halt = 1;
    }
};


#endif // INSTRUCTION_H_INCLUDED
