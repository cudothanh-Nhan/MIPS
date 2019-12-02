#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;
// PROTOTYPE----------------------------------------------------------
// Regular Expression


#pragma region INSTRUCTION_INTERFACE
class Instruction {
protected:
public:
    static string extractName(string _instruction);
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
    string rs;
    string rt;
    string rd;
    const string NAME;
public:
    static string extractR(string _instruction);
    R_Format();
    R_Format(string _name) : NAME(_name){}
    void init(string _instruction);
    virtual string getName() = 0;
    virtual void execute() = 0;
    virtual ~R_Format(){}
};
void R_Format::init(string _instruction) {}
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
string Instruction::extractName(string _instruction){
    char name[10];
    int spaceCount = 0;
    int index = 0;
    while(1) {
        if(_instruction[index] != 32 ){
            name[index] = _instruction[index];
        }
        else break;
        index++;
    }
    name[index] = '\0';
    return name;
}
Add::Add() : R_Format("add"){}
string Add::getName(){
    return this->NAME;
}
void Add::execute(){}
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
    string name = Instruction::extractName(_instruction);
    cout << "Name: " << name << '\n';
    if(!name.compare("add")) return new Add;
    else if(!name.compare("subtract")) return new Subtract;
    else if(!name.compare("and")) return new And;
    else return nullptr;
}

// Replace int main() with int process()
int main(){
    string instruction = "add $t0, $t1, $t2";
    Instruction* ptr = navigationCommand(instruction);
    if(ptr != nullptr) 
        cout << "The Name of instruction is: " << ptr->getName();
    else
        cout << "Invalid instruction";
}

