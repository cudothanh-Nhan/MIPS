#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>

using namespace std;
// PROTOTYPE----------------------------------------------------------

#pragma region Prototype
string extractRs(string _instruction);
string extractRt(string _instruction);
int extractImm(string _instrution);
string extractName(string _instruction);
class Instruction {
protected:
public:
	Instruction() {};
	virtual void execute() = 0;
	virtual string getName() = 0;
	virtual ~Instruction() {}
};
class I_Format : public Instruction {
protected:
	string rs;
	string rt;
	string adress;
	const string NAME;
public:
	I_Format();
	I_Format(string _name) : NAME(_name) {}
	virtual string getName() = 0;
	virtual void execute() = 0;
	virtual I_Format* checkNext(string) = 0;
	virtual ~I_Format() {}
};

#pragma endregion Prototype

#pragma region extractInput
string extractName(string _instruction) {
	char name[10];
	int spaceCount = 0;
	int index = 0;
	while (1) {
		if (_instruction[index] != 32) {
			name[index] = _instruction[index];
		}
		else break;
		index++;
	}
	name[index] = '\0';
	return name;
}
string extractRs(string _instruction) {
	char rs[5];
	int index = 0;
	int count = 0;
	while (1) {
		if (_instruction[index] == '$') {
			while ((_instruction[index + count] != ' ') && (_instruction[index + count] != ',')) {
				rs[count] = _instruction[index + count];
				count++;
			}
			break;
		}
		index++;
	}
	rs[count] = '\0';
	return rs;
}
string extractRt(string _instruction) {
	char rt[5];
	int index = 0;
	int count = 0;
	while (_instruction[index] != '$') index++;
	index++;
	while (1) {
		if (_instruction[index] == '$') {
			while (1){
				rt[count] = _instruction[index + count];
				count++;
				if ((_instruction[index + count] == ' ') || (_instruction[index + count] == ',') || (_instruction[index + count] == ')')) break;
			}
			break;
		}
		index++;
	}
	rt[count] = '\0';
	return rt;
}
int extractImm(string _instruction) {
	char imm[100];
	int num = 0;
	int index = 0;
	int count = 0;
	bool dau = false;
	while (1) {
		if (((int(_instruction[index]) >= 48)) && (int(_instruction[index] <= 57))) {
			if ((_instruction[index - 1] == ' ') || (_instruction[index - 1] == ',') || (_instruction[index - 1] == '-')) {
				if (_instruction[index - 1] == '-') dau = true;
				while (1) {
					imm[count] = _instruction[index + count];
					count++;
					if ((_instruction[index + count] == '\0') || (_instruction[index + count] == ' ') || (_instruction[index + count] == '(')) break;
				}
			}
		}
		if (count != 0) break;
		index++;
	}
	for (int i = count - 1; i >= 0; i--) {
			num += (int(imm[i]) - 48) * pow(10, count - i - 1);
	}
	if (dau == true) num = -num;
	return num;
}
#pragma endregion extractInput

#pragma region Prototype Subclass

class lw : public I_Format {
protected:
public:
	Lw();
	string getName();
	void execute();
	I_Format* checkNext(string);
	~Lw();
};

class sw : public I_Format {
protected:
public:
	sw();
	string getName();
	void execute();
	I_Format* checkNext(string);
	~sw();
};

class addi : public I_Format {
protected:
public:
	addi();
	string getName();
	void execute();
	I_Format* checkNext(string);
	~addi();
};
#pragma endregion Prototype Subclass

#pragma region lw

Lw::Lw() : I_Format("lw") {}
string Lw::getName() {
	return this->NAME;
}
void Lw::execute() {}
I_Format* Lw::checkNext(string _instruction) {
	string _name = extractName(_instruction);
	if (!NAME.compare(_name)) {
		return new Lw;
	}
	else {
		return sw().checkNext(_name);
	}
}
lw::~lw() {
	cout << "Destructor A called\n";
}

#pragma endregion lw

#pragma region sw

sw::sw() : I_Format("sw") {}
string sw::getName() {
	return this->NAME;
}
void sw::execute() {}
sw::~sw() {
	cout << "Destructor B called\n";
}
I_Format* sw::checkNext(string _name) {
	if (!NAME.compare(_name)) {
		return new sw;
	}
	else {
		return addi().checkNext(_name);
	}
}

#pragma endregion sw

#pragma region addi

void addi::execute() {}
I_Format* addi::checkNext(string _name) {
    if (!NAME.compare(_name)) {
		return new sw;
	}
	else {
		return nullptr;
	}
}

I_Format* navigationCommand(string _instruction) {
	string name = extractName(_instruction);
	return lw().checkNext(name);
}

#pragma endregion addi


// Replace int main() with int process()
int main() {
	string instruction = "li $a1, 90";
    string name = extractName(instruction);
	cout << name << endl;
	name = extractRs(instruction);
	cout << name << endl;
	name = extractRt(instruction);
	cout << name << endl;
	int num = extractImm(instruction);
	cout << num;
	Instruction* ptr = navigationCommand(instruction);
	if (ptr != nullptr)
		cout << "The Name of instruction is: " << ptr->getName();
	else
		cout << "Invalid instruction";
    return 0;
}
