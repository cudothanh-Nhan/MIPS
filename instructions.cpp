#include <iostream>
#include <iomanip>
#include <string.h>
#include "Serial.h"
#include "getWord.h"
#include "getRegister.h"
#include "getNumber.h"
#include "register.h"
#include "fileAssembly.h"

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

class I_Format : public Instruction {
protected:
	string rs;
	string rt;
	int imm;
	const string NAME;
public:
	I_Format();
	I_Format(string _name) : NAME(_name) {}
	virtual string getName() = 0;
	virtual void execute() = 0;
	virtual ~I_Format() {}
	void init(string _instruction);
};
void I_Format::init(string _instruction){
	rs = getRegister(_instruction, 1);
	rt = getRegister(_instruction, 2);
	imm = getNumbers(_instruction);
}
#pragma endregion END

#pragma region COMMAND_INTERFACE 
// R Format ----------------------------------------
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
// I FORMAT--------------------------------------

class Addi : public I_Format {
protected:
public:
	Addi();
	string getName();
	void execute();
	~Addi();
};

class Andi : public I_Format {
protected:
public:
	Andi();
	string getName();
	void execute();
	~Andi();
};

class Ori : public I_Format {
protected:
public:
	Ori();
	string getName();
	void execute();
	~Ori();
};
class Slti : public I_Format {
protected:
public:
	Slti();
	string getName();
	void execute();
	~Slti();
};

class Li : public I_Format {
protected:
public:
	Li();
	string getName();
	void execute();
	~Li();
};
class Lw : public I_Format {
protected:
public:
	Lw();
	string getName();
	void execute();
	~Lw();
};
#pragma endregion END

#pragma region IMPLEMENT_COMMAND

Add::Add() : R_Format("add"){}
string Add::getName(){
    return this->NAME;
}
void Add::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue(rs) + reg.getRegisterValue(rt));
    cmd.write(rd, reg.getRegisterValue(rd));
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
// I FORMAT----------------------------------------------------------


Addi::Addi() : I_Format("addi") {}
string Addi::getName() {
	return this->NAME;
}
void Addi::execute() {
	int temp;
	temp = reg.getRegisterValue(rt) + imm;
	reg.setRegisterValue(rs, temp);
	cmd.write(rs, reg.getRegisterValue(rs));
}
Addi::~Addi() {
	cout << "Destructor Addi called\n";
}




Andi::Andi() : I_Format("andi") {}
string Andi::getName() {
	return this->NAME;
}
void Andi::execute() {
	int temp;
	temp = reg.getRegisterValue(rt) & imm;
	reg.setRegisterValue(rs, temp);
	cmd.write(rs, reg.getRegisterValue(rs));
}
Andi::~Andi() {
	cout << "Destructor Andi called\n";
}

Ori::Ori() : I_Format("ori") {}
string Ori::getName() {
	return this->NAME;
}
void Ori::execute() {
	int temp;
	temp = reg.getRegisterValue(rt) | imm;
	reg.setRegisterValue(rs, temp);
	cmd.write(rs, reg.getRegisterValue(rs));
}
Ori::~Ori() {
	cout << "Destructor Ori called\n";
}

Slti::Slti() : I_Format("slti") {}
string Slti::getName() {
	return this->NAME;
}
void Slti::execute() {
	int temp;
	if (reg.getRegisterValue(rt) < imm) reg.setRegisterValue(rs, 1);
	else reg.setRegisterValue(rs,0);
	cmd.write(rs, reg.getRegisterValue(rs));
}
Slti::~Slti() {
	cout << "Destructor Slti called\n";
}

Li::Li() : I_Format("li") {}
string Li::getName() {
	return this->NAME;
}
void Li::execute() {
	reg.setRegisterValue(rs, imm);
    cout << reg.getRegisterValue(rs) << '\n';
	cmd.write(rs, reg.getRegisterValue(rs));
}
Li::~Li() {
	cout << "Destructor Li called\n";
}

Lw::Lw() : I_Format("lw") {}
string Lw::getName() {
	return this->NAME;
}
void Lw::execute() {
	// int temp;
	// temp = reg.getAddressValue | imm;
	// reg.setRegisterValue(rs, temp);
	// cmd.write(rs, reg.getRegisterValue(rs));
}
Lw::~Lw() {
	cout << "Destructor Ordi called\n";
}
#pragma endregion END



Instruction* navigationCommand(string _instruction){
    string name = getWord(_instruction, 1);
    if(!name.compare("add")) return new Add;
    else if(!name.compare("subtract")) return new Subtract;
    else if(!name.compare("and")) return new And;
    else if(!name.compare("sll")) return new Sll;
    else if(!name.compare("sll")) return new Sll;
    else if(!name.compare("addi")) return new Addi;
    else if(!name.compare("andi")) return new Andi;
    else if(!name.compare("ori")) return new Ori;
	else if(!name.compare("slti")) return new Slti;	
	else if(!name.compare("li")) return new Li;
    else return nullptr;
}
void setup() {
    cmd.init();
    reg.init();
    cmd.pause();
}
void printToConsole() {
    cmd.init();
    cmd.pause();
}
// Replace int main() with int process()
int main(){
    setup();
    FileAssembly fileIn("assembly.txt");
    while(fileIn.getInstruction(reg.getRegisterValue("pc")).compare("")) {
        string instruction = fileIn.getInstruction(reg.getRegisterValue("pc"));
        Instruction* ptr = navigationCommand(instruction);
        ptr->init(instruction);
        ptr->execute();
        printToConsole();
        reg.setRegisterValue("pc", reg.getRegisterValue("pc") + 4);
    }

}
