#ifndef INSTRUCTION
#define INSTRUCTION
#include <iostream>
#include <iomanip>
#include <string>
#include "Serial.h"
#include "getWord.h"
#include "getRegister.h"
#include "getNumber.h"
#include "register.h"
#include "coproc.h"
#include "fileAssembly.h"
#pragma region INSTRUCTION_INTERFACE
class System {
public:
    static string consoleField;
    void execute();
};
static Register reg("registerList.txt");
static Coproc cop("coprocList.txt");
static Serial cmd;
static FileAssembly fileIn;
static System sys;
string System::consoleField = "Console Field: \n";
void System::execute() {
    int option = reg.getRegisterValue("$v0");
    switch(option) {
        case 1:
            consoleField.append(to_string(reg.getRegisterValue("$a0")));
            break; 
        case 4:
            consoleField.append((char*)reg.getAddressValue("$a0"));
            break;
        case 5:
            int temp = 0;
            cin >> temp;
            consoleField.append(to_string(temp));
            reg.setRegisterValue("$a0", temp);
            cmd.write("$a0", temp);
    }
}
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
    if(getRegister(_instruction, 3).compare("")) {
        rd = getRegister(_instruction, 1);
        rs = getRegister(_instruction, 2);
        rt = getRegister(_instruction, 3);
    }
    else if(getRegister(_instruction, 2).compare("")) {
        rs = getRegister(_instruction, 1);
        rd = rs;
        rt = getRegister(_instruction, 2);    
    }
    else {
        rt = "";
        rs = getRegister(_instruction, 1);
        rd = rs;
    }
    shamt = getNumbers(_instruction);
}

class I_Format : public Instruction {
protected:
	string rs;
	string rt;
	int imm = 0;
    string label = "";
    string var = "";
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
    if (getWord(_instruction, 4) != ""){
        label = getWord(_instruction, 4);
    }
    else var = getWord(_instruction, 3);
}

class J_Format : public Instruction {
protected:
	string nameLabel;
	const string NAME;
public:
	J_Format();
	J_Format(string _name) : NAME(_name) {}
	virtual string getName() = 0;
	virtual void execute() = 0;
	virtual ~J_Format() {}
	void init(string _instruction);
};
void J_Format::init(string _instruction){
	nameLabel = getWord(_instruction, 2);
}

#pragma endregion END
#pragma region R-Fomat command Interface
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
class Srl : public R_Format {
protected:
public:
    Srl();
    string getName();
    void execute();
    ~Srl();
};
class Mult : public R_Format {
protected:
public:
    Mult();
    string getName();
    void execute();
    ~Mult();
};
class Div : public R_Format {
protected:
public:
    Div();
    string getName();
    void execute();
    ~Div();
};
class Jr : public R_Format {
protected:
public:
    Jr();
    string getName();
    void execute();
    ~Jr();
};
class Mfhi : public R_Format {
protected:
public:
    Mfhi();
    string getName();
    void execute();
    ~Mfhi();
};
class Mflo : public R_Format {
protected:
public:
    Mflo();
    string getName();
    void execute();
    ~Mflo();
};
class Sltu : public R_Format {
protected:
public:
    Sltu();
    string getName();
    void execute();
    ~Sltu();
};
#pragma endregion R-Format command Interface
#pragma region I-Format command Interface

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
class Beq : public I_Format {
protected:
public:
    Beq();
    string getName();
    void execute();
    ~Beq();
};
class Bne : public I_Format {
protected:
public:
    Bne();
    string getName();
    void execute();
    ~Bne();
};
class La : public I_Format {
protected:
public:
    La();
    string getName();
    void execute();
    ~La();
};
class Lw : public I_Format {
protected:
public:
	Lw();
	string getName();
	void execute();
	~Lw();
};
class Sw : public I_Format {
protected:
public:
    Sw();
    string getName();
    void execute();
    ~Sw();
};
class Lh : public I_Format {
protected:
public:
    Lh();
    string getName();
    void execute();
    ~Lh();
};
class Sh : public I_Format {
protected:
public:
    Sh();
    string getName();
    void execute();
    ~Sh();
};
class Lb : public I_Format {
protected:
public:
    Lb();
    string getName();
    void execute();
    ~Lb();
};
class Sb : public I_Format {
protected:
public:
    Sb();
    string getName();
    void execute();
    ~Sb();
};
#pragma endregion I-Format Interface
#pragma region J-Format command Interface
class Jump : public J_Format {
public:
	Jump();
	string getName();
	void execute();
	~Jump();
};
class Jal : public J_Format {
public:
    Jal();
    string getName();
    void execute();
    ~Jal();
};
#pragma endregion J-Format command Interface
#pragma region R-Format Command Implementation
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
    int temp = reg.getRegisterValue(rt);
    temp << shamt;
    reg.setRegisterValue(rs, temp);
    cmd.write(rs, reg.getRegisterValue(rs));
}
Sll::~Sll(){}

Srl::Srl() : R_Format("srl"){}
string Srl::getName(){
    return this->NAME;
}
void Srl::execute(){
    int temp = reg.getRegisterValue(rt);
    temp >> shamt;
    reg.setRegisterValue(rs, temp);
    cmd.write(rs, reg.getRegisterValue(rs));
}
Srl::~Srl(){}

Mult::Mult() : R_Format("mult"){}
string Mult::getName(){
    return this->NAME;
}
void Mult::execute(){
    reg.setRegisterValue("hi", reg.getRegisterValue(rs) * reg.getRegisterValue(rt));
    cmd.write("hi", reg.getRegisterValue("hi"));
    reg.setRegisterValue("lo", reg.getRegisterValue(rs) * reg.getRegisterValue(rt));
    cmd.write("lo", reg.getRegisterValue("lo"));
}
Mult::~Mult(){}

Div::Div() : R_Format("div"){}
string Div::getName(){
    return this->NAME;
}
void Div::execute(){
    reg.setRegisterValue("hi", reg.getRegisterValue(rs) % reg.getRegisterValue(rt));
    cmd.write("hi", reg.getRegisterValue("hi"));
    reg.setRegisterValue("lo", reg.getRegisterValue(rs) / reg.getRegisterValue(rt));
    cmd.write("lo", reg.getRegisterValue("lo"));
}
Div::~Div(){}

Jr::Jr() : R_Format("jr"){}
string Jr::getName(){
    return this->NAME;
}
void Jr::execute(){
    reg.setRegisterValue("pc", fileIn.getLabelAddress(rs));
}
Jr::~Jr(){}

Mfhi::Mfhi() : R_Format("mfhi"){}
string Mfhi::getName(){
    return this->NAME;
}
void Mfhi::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue("hi"));
    cmd.write(rd, reg.getRegisterValue(rd));
}
Mfhi::~Mfhi(){}

Mflo::Mflo() : R_Format("mflo"){}
string Mflo::getName(){
    return this->NAME;
}
void Mflo::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue("lo"));
    cmd.write(rd, reg.getRegisterValue(rd));
}
Mflo::~Mflo(){}

Sltu::Sltu() : R_Format("sltu"){}
string Sltu::getName(){
    return this->NAME;
}
void Sltu::execute(){
    if(reg.getRegisterValue(rs) < reg.getRegisterValue(rt)) reg.setRegisterValue(rd, 1);
    else reg.setRegisterValue(rd, 0);
    cmd.write(rd, reg.getRegisterValue(rd));
}
Sltu::~Sltu(){}
#pragma endregion R-Format Command Implementation
#pragma region I-Format Command Implementation
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
	cmd.write(rs, reg.getRegisterValue(rs));
}
Li::~Li() {
	cout << "Destructor Li called\n";
}

Beq::Beq() : I_Format("beq") {}
string Beq::getName() {
    return this->NAME;
}
void Beq::execute() {
    if (!rt.compare("")) {
        if (reg.getRegisterValue(rs) == imm){
            reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
        }
        return;
    }
    else {
        if(reg.getRegisterValue(rs) == reg.getRegisterValue(rt)) {
            reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);        
        }
        return;
    }        
    //if (rs.compare(rt) == 0) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Beq::~Beq() {
    cout << "Destructor Beq called\n";
}

Bne::Bne() : I_Format("bne") {}
string Bne::getName() {
    return this->NAME;
}
void Bne::execute() {
    if (!rt.compare("")){
        if (reg.getRegisterValue(rs) != imm) {
            reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
        }
        return;
    }
    if (rs.compare(rt) != 0) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Bne::~Bne() {
    cout << "Destructor Bne called\n";
}
La::La() : I_Format("la") {};
string La::getName(){
    return this->NAME;
}
void La::execute() {
    if ((var.compare("")) && (imm == 0)){
        reg.setRegisterAddress(rs, (int*)(fileIn.getDataAddress(var)));
        cmd.write(rs, reg.getRegisterValue(rs));
        return;
    }
    else {
        reg.setRegisterValue(rs, imm);
        cmd.write(rs, reg.getRegisterValue(rs));
    }
}
La::~La(){
    cout << "Destructor La called\n";
}
Lw::Lw() : I_Format("lw") {}
string Lw::getName() {
	return this->NAME;
}
void Lw::execute() {
    if (rt.compare("")) {
        reg.setRegisterValue(rs, *(int*)(reg.getAddressValue(rt) + imm/4));
        cmd.write(rs, reg.getRegisterValue(rs));
        return;
    }
    else if(var.compare("")) {
        reg.setRegisterValue(rs, *(int*)(fileIn.getDataAddress(var)));
        cmd.write(rs, reg.getRegisterValue(rs));
    }

}
Lw::~Lw() {
	cout << "Destructor Lw called\n";
}
Sw::Sw() : I_Format("sw") {}
string Sw::getName() {
	return this->NAME;
}
void Sw::execute() {
    if (var.compare("")) {
        *(int*)(reg.getAddressValue(rt) + imm/4) = reg.getRegisterValue(rs);
        return;
    }
}
Sw::~Sw() {
	cout << "Destructor Sw called\n";
}
Lh::Lh() : I_Format("lh") {}
string Lh::getName() {
	return this->NAME;
}
void Lh::execute() {
    if (var.compare("")) {
        int* temp = (int*)(reg.getAddressValue(rt) + imm/4);
        reg.setRegisterValue(rs, int16_t(*temp));
        cmd.write(rs, reg.getRegisterValue(rs));
        return;
    }
}
Lh::~Lh() {
	cout << "Destructor Lh called\n";
}
Sh::Sh() : I_Format("sh") {}
string Sh::getName() {
	return this->NAME;
}
void Sh::execute() {
    if (var.compare("")) {
        *(int*)(reg.getAddressValue(rt) + imm/4) = int16_t(reg.getRegisterValue(rs));
        return;
    }
}
Sh::~Sh() {
	cout << "Destructor Sh called\n";
}
Lb::Lb() : I_Format("lb") {}
string Lb::getName() {
	return this->NAME;
}
void Lb::execute() {
    if (var.compare("")) {
        int* temp = (int*)(reg.getAddressValue(rt) + imm);
        reg.setRegisterValue(rs, int8_t(*temp));
        cmd.write(rs, reg.getRegisterValue(rs));
        return;
    }
}
Lb::~Lb() {
	cout << "Destructor Lb called\n";
}
Sb::Sb() : I_Format("sb") {}
string Sb::getName() {
	return this->NAME;
}
void Sb::execute() {
    if (var.compare("")) {
        *(int*)(reg.getAddressValue(rt) + imm) = int8_t(reg.getRegisterValue(rs));
        return;
    }
}
Sb::~Sb() {
	cout << "Destructor Sb called\n";
}
#pragma endregion I-Format Command Implementation
#pragma region J-Format Command Implementation
Jump::Jump() : J_Format("j"){};
string Jump::getName() {
	return this->NAME;
}
void Jump::execute() {
	int labelJump = fileIn.getLabelAddress(nameLabel);
	reg.setRegisterValue("pc",labelJump - 4);
    cmd.write("pc",reg.getRegisterValue("pc"));
}
Jump::~Jump(){};

Jal::Jal() : J_Format("jal"){};
string Jal::getName(){
    return this->NAME;
}
void Jal::execute(){
    int labelJump = fileIn.getLabelAddress(nameLabel);
    reg.setRegisterValue("$ra", reg.getRegisterValue("pc") + 4);
    cmd.write("$ra", reg.getRegisterValue("$ra"));
    reg.setRegisterValue("pc",labelJump - 4);
    cmd.write("pc", reg.getRegisterValue("pc"));
}
Jal::~Jal(){};
#pragma endregion J-Format Command Implementation
#endif
