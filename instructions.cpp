#include <iostream>
#include <iomanip>
#include <string.h>
#include "Serial.h"
#include "getWord.h"
#include "getRegister.h"
#include "getNumber.h"
#include "register.h"

using namespace std;
// PROTOTYPE----------------------------------------------------------
// Regular Expression

static Register reg("registerList.txt");
static Serial cmd;
#pragma region INSTRUCTION_INTERFACE
class Instruction {
protected:
public:
    Instruction(){};
    virtual void init(string _instruction) = 0;
    virtual void execute() = 0;
    virtual string getName() = 0;
    virtual ~Instruction(){}
};
#pragma endregion END

#pragma region FORMAT_INTERFACE
class R_Format : public Instruction {
protected:
    string rd;
    string rs;
    string rt;
    int shamt;
    const string NAME;
public:
    R_Format(string _name) : NAME(_name){}
    void init(string _instruction);
    virtual string getName() = 0;
    virtual void execute() = 0;
    virtual ~R_Format(){}
};
void R_Format::init(string _instruction) {
    rd = getRegister(_instruction, 1);
    rt = getRegister(_instruction, 2);
    rs = getRegister(_instruction, 3);
    shamt = getNumbers(_instruction);
}
#pragma endregion END

#pragma region COMMAND_INTERFACE 
class Add : public R_Format {
protected:
public:
    Add();
    string getName();
    void execute();
    ~Add();
};

class Subtract : public R_Format {
protected:
public:
    Subtract();
    string getName();
    void execute();
    ~Subtract();
};


class And : public R_Format {
protected:
public:
    And();
    string getName();
    void execute();
    ~And();
};
class Sll : public R_Format {
protected:
public:
    Sll();
    string getName();
    void execute();
    ~Sll();
};

#pragma endregion END

#pragma region IMPLEMENT_COMMAND

Add::Add() : R_Format("add"){}
string Add::getName(){
    return this->NAME;
}
void Add::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue(rs) + reg.getRegisterValue(rt));
}
Add::~Add(){}

Subtract::Subtract() : R_Format("substract"){}
string Subtract::getName(){
    return this->NAME;
}
void Subtract::execute(){}
Subtract::~Subtract(){}

And::And() : R_Format("and"){}
string And::getName(){
    return this->NAME;
}
void And::execute(){}
And::~And(){}

Sll::Sll() : R_Format("sll"){}
string Sll::getName(){
    return this->NAME;
}
void Sll::execute(){
    int temp = reg.getRegisterValue(rt) * pow(2, shamt);
    reg.setRegisterValue(rd, temp);
    cmd.write(rs, reg.getRegisterValue(rs));
}
Sll::~Sll(){}
#pragma endregion END



Instruction* navigationCommand(string _instruction){
    string name = getWord(_instruction, 1);
    if(!name.compare("add")) return new Add;
    else if(!name.compare("subtract")) return new Subtract;
    else if(!name.compare("and")) return new And;
    else if(!name.compare("sll")) return new Sll;
    else return nullptr;
}
void setup() {
    cmd.init();
    reg.init();
}
void printToConsole() {
    cmd.init();
    cmd.pause();
}
// Replace int main() with int process()
int main(){
    setup();
    reg.setRegisterValue("$a1", 10);
    string instruction = "sll $a0, $a1, 3";
    Instruction* ptr = navigationCommand(instruction);
    ptr->init(instruction);
    ptr->execute();
    cout << reg.getRegisterValue("$a0");
}

