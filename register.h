// Register Lib Done
#ifndef REGISTER
#define REGISTER

#include <string>
#include <fstream>
using namespace std;

class Register {
protected:
    struct RegisterNode {
        string name;
        int value;
        int* address;
        RegisterNode* next;
    };
    string linkFile;
    Register::RegisterNode* root;
public:
    Register(string _linkFile);
    void init();
    void setRegisterAddress(string registerName, int* ptr);
    void setRegisterValue(string registerName, int value);
    int getRegisterValue(string registerName);
    int* getAddressValue(string registerName);
};

Register::Register(string _linkFile) {
    this->linkFile = _linkFile;
    this->root = nullptr;
}
void Register::init() {
    ifstream registerList;
    registerList.open(this->linkFile, istream::binary);
    int countRegister = 1;
    RegisterNode* preRegisterNode;
    while(!registerList.eof()) {
        RegisterNode* newNode = new RegisterNode;
        newNode->value = 0;
        newNode->address = nullptr;
        registerList >> newNode->name;
        if(countRegister == 1) {
            root = newNode;
            newNode->next = nullptr;
            countRegister++;
        }
        else {
            newNode->next = root;
            root = newNode;
        }
    }
}
void Register::setRegisterAddress(string registerName, int* ptr) {
    registerName = getWord(registerName, 1);
    RegisterNode* seeker;
    seeker = root;
    while(seeker->next != nullptr) {
        if(!seeker->name.compare(registerName)) {
            seeker->address = ptr;
            seeker->value = *(int*)(&seeker->address);
        }
        seeker = seeker->next;
    }
}
void Register::setRegisterValue(string registerName, int _value) {
    registerName = getWord(registerName, 1);
    RegisterNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            seeker->value = _value;
            seeker->address = (int*)seeker->value;
        }
        seeker = seeker->next;
    }
}
int* Register::getAddressValue(string registerName) {
    registerName = getWord(registerName, 1);
    RegisterNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            return seeker->address;
        }
        seeker = seeker->next;
    }
    return nullptr;
}
int Register::getRegisterValue(string registerName) {
    registerName = getWord(registerName, 1);
    RegisterNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            return seeker->value;
        }
        seeker = seeker->next;
    }
    return 0;
}
#endif