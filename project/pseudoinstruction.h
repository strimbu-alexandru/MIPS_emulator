#ifndef PSEUDOINSTRUCTION_H_INCLUDED
#define PSEUDOINSTRUCTION_H_INCLUDED

#include <vector>
#include <string>

class Pseudoinstruction {
public:
    std::vector<int> args;
    std::string label;
    Pseudoinstruction(const std::string type) {
        this->type = type;
        this->args = std::vector<int>();
        this->label = "";
    }
    std::string getType() {
        return type;
    }
private:
    std::string type;
};

#endif // PSEUDOINSTRUCTION_H_INCLUDED
