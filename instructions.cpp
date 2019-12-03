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
    rs = getRegister(_instruction, 2);
    rt = getRegister(_instruction, 3);
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
#pragma endregion END



Instruction* navigationCommand(string _instruction){
    string name = getWord(_instruction, 1);
    if(!name.compare("add")) return new Add;
    else if(!name.compare("subtract")) return new Subtract;
    else if(!name.compare("and")) return new And;
    else return nullptr;
}

// Replace int main() with int process()
int main(){
    Serial cmd;
    cmd.init();
    system("pause");
    reg.init();
    string instruction = "add $t0, $t1, $t2";
    Instruction* ptr = navigationCommand(instruction);
    ptr->init(instruction);

    reg.setRegisterValue("$t1", 10);
    cmd.write("$t1", 10);
    cmd.init();
    system("pause");
    reg.setRegisterValue("$t2", 17);
    cmd.write("$t2", 17);
    cmd.init();
    system("pause");
    ptr->execute();
    cmd.write("$t0", reg.getRegisterValue("$t0"));
    cmd.init();
    system("pause");
    // if(ptr != nullptr) 
    //     cout << "The Name of instruction is: " << ptr->getName();
    // else
    //     cout << "Invalid instruction";
}

