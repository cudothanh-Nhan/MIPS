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
public:
    const char* registerName[35] {"$zero", "$at", "$v0", "$v1", "$a0", "$a1","$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "pc", "hi", "lo"};
    Serial();
    void print();
    int write(string, int);
    void printCurrentLine(int, int);
    void pause();
};

Serial::Serial(){
    for (int i = 0; i < 35; i++) registerValue[i] = 0;
}
void Serial::print(){
    system("cls");
    cout << setw(18) << left << "   Register Name" << "|" << setw(18) << left << "  Register Number" << " |" << setw(18) << " Value" << endl;
    cout << "----------------------------------------------" << endl;
    for (int i = 0; i < 32; i++) {
        cout << "  "<< left << setw(16) << registerName[i] << "| " << left << setw(18) << i << "| " << left << setw(18) << registerValue[i] << endl;
    }
    for (int i = 32; i < 35; i++) {
        cout << "  " << left << setw(16) << registerName[i] << "|                   " << "| " << setw(18) << registerValue[i] << endl;
    }
    cout << "----------------------------------------------" << endl;
}
int Serial::write(string registerInput, int valueInput){
    for (int i = 0; i < 35; i++){
        if (!registerInput.compare(registerName[i])){
            registerValue[i] = valueInput;
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