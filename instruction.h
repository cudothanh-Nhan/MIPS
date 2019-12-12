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
        case 2:
            consoleField.append(to_string(cop.getCoprocValue("$f12")));
            break; 
        case 4:
            consoleField.append((char*)reg.getAddressValue("$a0"));
            break;
        case 5: {
            int temp = 0;
            cin >> temp;
            consoleField.append(to_string(temp));
            reg.setRegisterValue("$a0", temp);
            cmd.write("$a0", temp);
            break;
        }
        case 6:
            string temp;
            cin >> temp;
            consoleField.append(temp);
            consoleField.append("\n");
            cop.setCoprocValue("$f0", stof(temp));
            cmd.write("$f0", stof(temp));
            break;
    }
}
class Instruction {
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
    bool full = 1;
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
        full = 1;
    }
    else if(getRegister(_instruction, 2).compare("")) {
        rs = getRegister(_instruction, 1);
        rd = rs;
        rt = getRegister(_instruction, 2);
        full = 0;    
    }
    else {
        rt = "";
        rs = getRegister(_instruction, 1);
        rd = rs;
        full = -1;
    }
    shamt = getNumbers(_instruction);
}

class I_Format : public Instruction {
protected:
	string rs = "";
	string rt = "";
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
	this->rs = getRegister(_instruction, 1);
	this->rt = getRegister(_instruction, 2);
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
class Absolute : public R_Format {
protected:
public:
    Absolute();
    string getName();
    void execute();
    ~Absolute();
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

class Or : public R_Format {
protected:
public:
    Or();
    string getName();
    void execute();
    ~Or();
};

class Xor : public R_Format {
protected:
public:
    Xor();
    string getName();
    void execute();
    ~Xor();
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
class Mtc1 : public R_Format {
protected:
public:
    Mtc1();
    string getName();
    void execute();
    ~Mtc1();
};

class Mfc1 : public R_Format {
protected:
public:
    Mfc1();
    string getName();
    void execute();
    ~Mfc1();
};
class Move : public R_Format {
protected:
public:
    Move();
    string getName();
    void execute();
    ~Move();
};
class MoveS : public R_Format {
protected:
public:
    MoveS();
    string getName();
    void execute();
    ~MoveS();
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
class Subi : public I_Format {
protected:
public:
	Subi();
	string getName();
	void execute();
	~Subi();
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
class Swc1 : public I_Format {
protected:
public:
    Swc1();
    string getName();
    void execute();
    ~Swc1();
};
class Lwc1 : public I_Format {
protected:
public:
    Lwc1();
    string getName();
    void execute();
    ~Lwc1();
};
class Bgez : public I_Format {
protected:
public:
    Bgez();
    string getName();
    void execute();
    ~Bgez();
};
class Beqz : public I_Format {
protected:
public:
    Beqz();
    string getName();
    void execute();
    ~Beqz();
};
class Bgt : public I_Format {
protected:
public:
    Bgt();
    string getName();
    void execute();
    ~Bgt();
};
class Bge : public I_Format {
protected:
public:
    Bge();
    string getName();
    void execute();
    ~Bge();
};
class Blt : public I_Format {
protected:
public:
    Blt();
    string getName();
    void execute();
    ~Blt();
};
class Ble : public I_Format {
protected:
public:
    Ble();
    string getName();
    void execute();
    ~Ble();
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

Absolute::Absolute() : R_Format("absolute"){}
string Absolute::getName(){
    return this->NAME;
}
void Absolute::execute(){
    reg.setRegisterValue(rd, abs(reg.getRegisterValue(rs)));
    cmd.write(rd, reg.getRegisterValue(rd));
}
Absolute::~Absolute(){}

Subtract::Subtract() : R_Format("sub"){}
string Subtract::getName(){
    return this->NAME;
}
void Subtract::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue(rs) - reg.getRegisterValue(rt));
    cmd.write(rd, reg.getRegisterValue(rd));
}
Subtract::~Subtract(){}

And::And() : R_Format("and"){}
string And::getName(){
    return this->NAME;
}
void And::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue(rs) & reg.getRegisterValue(rt));
    cmd.write(rd, reg.getRegisterValue(rd));
}
And::~And(){}

Or::Or() : R_Format("or"){}
string Or::getName(){
    return this->NAME;
}
void Or::execute(){
    reg.setRegisterValue(rd, reg.getRegisterValue(rs) | reg.getRegisterValue(rt));
    cmd.write(rd, reg.getRegisterValue(rd));
}
Or::~Or(){}

Xor::Xor() : R_Format("Xor"){}
string Xor::getName(){
    return this->NAME;
}
void Xor::execute(){
    if(full == 1) {
        reg.setRegisterValue(rd, reg.getRegisterValue(rs) ^ reg.getRegisterValue(rt));
        cmd.write(rd, reg.getRegisterValue(rd));
    }
    else {
        reg.setRegisterValue(rs, reg.getRegisterValue(rt) ^ shamt);
        cmd.write(rd, reg.getRegisterValue(rd));   
    }
}
Xor::~Xor(){}

Sll::Sll() : R_Format("sll"){}
string Sll::getName(){
    return this->NAME;
}
void Sll::execute(){
    int temp = reg.getRegisterValue(rt);
    temp = temp << shamt;
    reg.setRegisterValue(rs, temp);
    cmd.write(rs, reg.getRegisterValue(rs));
}
Sll::~Sll(){}

Srl::Srl() : R_Format("srl"){}
string Srl::getName(){
    return this->NAME;
}
void Srl::execute(){
    unsigned int temp = reg.getRegisterValue(rt);
    temp = temp >> shamt;
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

Mtc1::Mtc1() : R_Format("mtc1"){}
string Mtc1::getName(){
    return this->NAME;
}
void Mtc1::execute(){
    int temp = reg.getRegisterValue(rs);
    float* tempPtr = (float*)&temp;
    cop.setCoprocValue(rt, *tempPtr);
    cmd.write(rt, cop.getCoprocValue(rt));
}
Mtc1::~Mtc1(){}

Mfc1::Mfc1() : R_Format("mfc1"){}
string Mfc1::getName(){
    return this->NAME;
}
void Mfc1::execute(){
    float temp = cop.getCoprocValue(rt);
    int* tempPtr = (int*)&temp;
    reg.setRegisterValue(rs, *tempPtr);
    cmd.write(rs, reg.getRegisterValue(rs));
}
Mfc1::~Mfc1(){}

Move::Move() : R_Format("move"){}
string Move::getName(){
    return this->NAME;
}
void Move::execute(){
    reg.setRegisterValue(rs, reg.getRegisterValue(rt));
    cmd.write(rs, reg.getRegisterValue(rs));
}
Move::~Move(){}
MoveS::MoveS() : R_Format("mov.s"){}
string MoveS::getName(){
    return this->NAME;
}
void MoveS::execute(){
    cop.setCoprocValue(rs, cop.getCoprocValue(rt));
    cmd.write(rs, cop.getCoprocValue(rs));
}
MoveS::~MoveS(){}
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
Subi::Subi() : I_Format("subi") {}
string Subi::getName() {
	return this->NAME;
}
void Subi::execute() {
	int temp;
	temp = reg.getRegisterValue(rt) - imm;
	reg.setRegisterValue(rs, temp);
	cmd.write(rs, reg.getRegisterValue(rs)); 
}
Subi::~Subi() {
	cout << "Destructor Subi called\n";
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
    if (rt.compare("")) {
        *(int*)(reg.getAddressValue(rt) + imm/4) = reg.getRegisterValue(rs);
        return;
    }
    else if(var.compare("")) {
        *(int*)(fileIn.getDataAddress(var)) = reg.getRegisterValue(rs);
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

Swc1::Swc1() : I_Format("swc1") {}
string Swc1::getName() {
	return this->NAME;
}
void Swc1::execute() {
    if (rt.compare("")) {
        *(float*)(reg.getAddressValue(rt) + imm/4) = cop.getCoprocValue(rs);
        return;
    }
    else if (var.compare("")) {
        *(float*)(fileIn.getDataAddress(var)) = cop.getCoprocValue(rs);
        return;
    }
}
Swc1::~Swc1() {
	cout << "Destructor Swc1 called\n";
}

Lwc1::Lwc1() : I_Format("lwc1") {}
string Lwc1::getName() {
	return this->NAME;
}
void Lwc1::execute() {
    if (rt.compare("")) {
        cop.setCoprocValue(rs, *(float*)(cop.getCoprocAddressValue(rt) + imm/4));
        cmd.write(rs, cop.getCoprocValue(rs));
        return;
    }
    else if(var.compare("")) {
        cop.setCoprocValue(rs, *(float*)(fileIn.getDataAddress(var)));
        cmd.write(rs, cop.getCoprocValue(rs));
    }
}
Lwc1::~Lwc1() {
	cout << "Destructor Lwc1 called\n";
}
Bgez::Bgez() : I_Format("bgez") {}
string Bgez::getName() {
	return this->NAME;
}
void Bgez::execute() {
    if (reg.getRegisterValue(rs) >= 0) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Bgez::~Bgez() {
	cout << "Destructor Bgez called\n";
}
Beqz::Beqz() : I_Format("beqz") {}
string Beqz::getName() {
	return this->NAME;
}
void Beqz::execute() {
    if (reg.getRegisterValue(rs) == 0) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Beqz::~Beqz() {
	cout << "Destructor Beqz called\n";
}
Bgt::Bgt() : I_Format("bgt") {}
string Bgt::getName() {
	return this->NAME;
}
void Bgt::execute() {
    if (reg.getRegisterValue(rs) > reg.getRegisterValue(rt)) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Bgt::~Bgt() {
	cout << "Destructor Bgt called\n";
}
Bge::Bge() : I_Format("bge") {}
string Bge::getName() {
	return this->NAME;
}
void Bge::execute() {
    if (reg.getRegisterValue(rs) >= reg.getRegisterValue(rt)) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Bge::~Bge() {
	cout << "Destructor Bge called\n";
}
Blt::Blt() : I_Format("blt") {}
string Blt::getName() {
	return this->NAME;
}
void Blt::execute() {
    if (reg.getRegisterValue(rs) < reg.getRegisterValue(rt)) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Blt::~Blt() {
	cout << "Destructor Blt called\n";
}
Ble::Ble() : I_Format("ble") {}
string Ble::getName() {
	return this->NAME;
}
void Ble::execute() {
    if (reg.getRegisterValue(rs) <= reg.getRegisterValue(rt)) reg.setRegisterValue("pc", fileIn.getLabelAddress(label) - 4);
}
Ble::~Ble() {
	cout << "Destructor Ble called\n";
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
