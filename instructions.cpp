#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;
// PROTOTYPE----------------------------------------------------------

string extractRs(string _instruction);
string extractRt(string _instruction);
string extractRd(string _instrution);
string extractName(string _instruction);
class Instruction {
protected:
public:
    Instruction(){};
    virtual void execute() = 0;
    virtual string getName() = 0;
    virtual ~Instruction(){}
};
class R_Format : public Instruction {
protected:
    string rs;
    string rt;
    string rd;
    const string NAME;
public:
    R_Format();
    R_Format(string _name) : NAME(_name){}
    virtual string getName() = 0;
    virtual void execute() = 0;
    virtual R_Format* checkNext(string) = 0;
    virtual ~R_Format(){}
};

class Add : public R_Format {
protected:
public:
    Add();
    string getName();
    void execute();
    R_Format* checkNext(string);
    ~Add();
};

class Subtract : public R_Format {
protected:
public:
    Subtract();
    string getName();
    void execute();
    R_Format* checkNext(string);
    ~Subtract();
};

// IMPLEMENT CLASS------------------------------------------------------------
string extractName(string _instruction){
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
R_Format* Add::checkNext(string _instruction){
    string _name = extractName(_instruction);
    if(!NAME.compare(_name)) {
        return new Add;
    }
    else {
        return Subtract().checkNext(_name);
    }  
}
Add::~Add(){       
    cout << "Destructor A called\n";
}

Subtract::Subtract() : R_Format("substract"){}
string Subtract::getName(){
    return this->NAME;
}
void Subtract::execute(){}
Subtract::~Subtract(){       
    cout << "Destructor B called\n";
}
R_Format* Subtract::checkNext(string _name){
    if(!NAME.compare(_name)) {
        return new Subtract;
    }
    else {
        return nullptr;
    }
}

R_Format* navigationCommand(string _instruction){
    string name = extractName(_instruction);
    return Add().checkNext(name);
}
// Replace int main() with int process()
int main(){

    string instruction = "substract 123";
    Instruction* ptr = navigationCommand(instruction);
    if(ptr != nullptr) 
        cout << "The Name of instruction is: " << ptr->getName();
    else
        cout << "Invalid instruction";
}

