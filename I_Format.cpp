#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include "register.h"
#include "getNumber.h"
#include "getRegister.h"
#include "getWord.h"
#include "serial.h"

using namespace std;
// PROTOTYPE----------------------------------------------------------

static Register reg("registerList.txt");
Serial cmd;
#pragma region Prototype
// string extractRs(string _instruction);
// string extractRt(string _instruction);
// int extractImm(string _instrution);
// string extractName(string _instruction);
class Instruction {
protected:
public:
	static string extractName(string _instruction);
	Instruction() {};
	virtual void init(string _instruction) = 0;
	virtual void execute() = 0;
	virtual string getName() = 0;
	virtual ~Instruction() {}
};
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

#pragma endregion Prototype

#pragma region init I-Format

void I_Format::init(string _instruction){
	rs = getRegister(_instruction, 1);
	rt = getRegister(_instruction, 2);
	imm = getNumbers(_instruction);
}

#pragma endregion init I-Format

#pragma region Prototype Subclass

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

#pragma endregion Prototype Subclass

#pragma region Addi

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

#pragma endregion Addi

#pragma region Andi
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
#pragma endregion Andi

#pragma region Ordi
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
#pragma endregion Ordi

#pragma region Slti
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
#pragma endregion Slti

#pragma region Li
Li::Li() : I_Format("li") {}
string Li::getName() {
	return this->NAME;
}
void Li::execute() {
	reg.setRegisterValue(rs, imm);
	cmd.write(rs, reg.getRegisterValue(rs));
}
Li::~Li() {
	cout << "Destructor Li called\n";
}
#pragma endregion Li

#pragma region Lw
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

#pragma endregion Lw
I_Format* navigationCommand(string _instruction) {
	string name = getWord(_instruction, 1);
	cout << "Name: " << name << '\n';
    if(!name.compare("addi")) return new Addi;
    else if(!name.compare("andi")) return new Andi;
    else if(!name.compare("ori")) return new Ori;
	else if(!name.compare("slti")) return new Slti;	
	else if(!name.compare("li")) return new Li;
    else return nullptr;
}



// Replace int main() with int process()
int main() {
	string instruction = "addi $t1,$t2, 200";
	Instruction* ptr = navigationCommand(instruction);
	reg.init();
	ptr->init(instruction);
	cmd.init();
	cmd.pause();
	ptr->execute();
	cmd.init();
    return 0;
}
