#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
using namespace std;

class Serial {
    int registerValue[33];
public:
    const char* registerName[33] {"$zero", "$at", "$v0", "$v1", "$a0", "$a1","$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "pc"};
    Serial();
    void init();
    int write(string, int);
    void printCurrentLine(int, int);
};

Serial::Serial(){
    for (int i = 0; i < 33; i++) registerValue[i] = 0;
}
void Serial::init(){
    cout << setw(18) << "Register Name" << "|" << setw(18) << "Register Number" << " |" << setw(18) << "Value" << endl;
    for (int i = 0; i < 32; i++) cout << left << setw(18) << registerName[i] << "| " << left << setw(18) << i << "| " << left << setw(18) << registerValue[i] << endl;
    cout << left << setw(18) << registerName[32] << "|                   " << "| " << setw(18) << registerValue[32] << endl;
}
int Serial::write(string registerInput, int valueInput){
    for (int i = 0; i < 32; i++){
        if (!registerInput.compare(registerName[i])){
            registerValue[i] = valueInput;
            return 1;
        }
    }
    return 0;
}
void Serial::printCurrentLine(int currentLine, int totalLines){
    cout << "This is line " << currentLine << "/" << totalLines << endl;
}

int main(){
    Serial cmd;
    cmd.init();
    string registerInput;
    int valueInput, currentLine, totalLines;
    cout << "Nhap: " << endl;
    getline(cin, registerInput);
    cin >> valueInput >> currentLine >> totalLines;

    system("cls");
    if (cmd.write(registerInput, valueInput) == 1){
        cmd.init();
        cmd.printCurrentLine(currentLine, totalLines);
    } else cout << "Not valid input" << endl;
    cout << "Press any keys to exit...";
    getch();
    return 0;
}