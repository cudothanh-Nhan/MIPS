// Register Lib Done
#ifndef COPROC
#define COPROC

#include <string>
#include <fstream>
using namespace std;

class Coproc {
protected:
    struct CoprocNode {
        string name;
        float value;
        float* address;
        CoprocNode* next;
    };
    string linkFile;
    CoprocNode* root;
public:
    Coproc(string _linkFile);
    void init();
    void setCoprocAddress(string registerName, float* ptr);
    void setCoprocValue(string registerName, float value);
    float getCoprocValue(string registerName);
    float* getCoprocAddressValue(string registerName);
};

Coproc::Coproc(string _linkFile) {
    this->linkFile = _linkFile;
    this->root = nullptr;
}
void Coproc::init() {
    ifstream registerList;
    registerList.open(this->linkFile);
    int countRegister = 1;
    CoprocNode* preCoprocNode;
    while(!registerList.eof()) {
        CoprocNode* newNode = new CoprocNode;
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
void Coproc::setCoprocAddress(string registerName, float* ptr) {
    registerName = getWord(registerName, 1);
    CoprocNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            seeker->address = ptr;
            seeker->value = *(int*)(&seeker->address);
        }
        seeker = seeker->next;
    }
}
void Coproc::setCoprocValue(string registerName, float _value) {
    registerName = getWord(registerName, 1);
    CoprocNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            seeker->value = _value;
            seeker->address = (float*)(int)seeker->value;
        }
        seeker = seeker->next;
    }
}
float* Coproc::getCoprocAddressValue(string registerName) {
    registerName = getWord(registerName, 1);
    CoprocNode* seeker;
    seeker = root;
    while(seeker != nullptr) {
        if(!seeker->name.compare(registerName)) {
            return seeker->address;
        }
        seeker = seeker->next;
    }
    return nullptr;
}
float Coproc::getCoprocValue(string registerName) {
    registerName = getWord(registerName, 1);
    CoprocNode* seeker;
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