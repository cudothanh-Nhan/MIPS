#ifndef SERIAL
#define SERIAL

#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
using namespace std;
static bool isExit = 0;
class Serial {
    int registerValue[35];
    int coprocValue[32];
public:
    const char* registerName[35] {"$zero", "$at", "$v0", "$v1", "$a0", "$a1","$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "pc", "hi", "lo"};
    const char* coprocName[32] {"$f0", "$f1", "$f2", "$f3", "$f4", "$f5","$f6", "$f7", "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
    "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23", "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"};
    Serial();
    void print();
    int write(string, double);
    void printCurrentLine(int, int);
    void pause();
};

Serial::Serial(){
    for (int i = 0; i < 35; i++) registerValue[i] = 0;
    for (int i = 0; i < 32; i++) coprocValue[i] = 0;
}
void Serial::print(){
    system("cls");
    cout << "                   REGISTER                                           COPROCESSOR 1" << endl << endl;
    cout << setw(18) << left << "   Register Name" << "|" << setw(18) << left << "  Register Number" << " |" << setw(18) << " Value"
    << setw(19) << "  Name" << "|" << setw(18) << " Float" << " |" << setw(18) << " Double"<< endl;
    cout << "----------------------------------------------          ---------------------------------------------------" << endl;
    for (int i = 0; i < 32; i++) {
        cout << "  "<< left << setw(16) << registerName[i] << "| " << left << setw(18) << i << "| " << left << setw(18) << registerValue[i] 
        << left << setw(18) << coprocName[i] << "| " << left << setw(18) << float(coprocValue[i]) << "| " << left << setw(18) << coprocValue[i] << endl;
    }
    for (int i = 32; i < 35; i++) {
        cout << "  " << left << setw(16) << registerName[i] << "|                   " << "| " << setw(18) << registerValue[i] << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
}
int Serial::write(string Input, double valueInput){
    for (int i = 0; i < 35; i++){
        if (!Input.compare(registerName[i])){
            registerValue[i] = int(valueInput);
            return 1;
        }
    }
    for (int i = 0; i < 32; i++){
        if (!Input.compare(coprocName[i])){
            coprocValue[i] = valueInput;
            return 1;
        }
    }
    return 0;
}
void Serial::pause() {
    char temp = getchar();
    if(temp == 'x') isExit = 1;
}
#endif