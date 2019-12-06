#ifndef GETTEXT
#define GETTEXT

#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include "getWord.h"	
using namespace std;

class FileAssembly {
protected:
    struct Label {
        string labelName;
        int labelAddress = -1;
        FileAssembly::Label* next = nullptr;
    };
	string linkFile;
	string text[100];
	int numberOfInstruction = 0;
    Label* labelArray = nullptr;
public:
    FileAssembly(string _linkFile);
	string getInstruction(int);
    int getLabelAddress(string);
};
FileAssembly::FileAssembly(string _linkFile) : linkFile(_linkFile){
// This is for TEXT PART
    int i = 0;
    string temp;
    ifstream fileIn;
    fileIn.open(_linkFile);
    while (!fileIn.eof()){
        getline(fileIn, temp);
        if (int(temp.find(".text")) >= 0){
            while (!fileIn.eof()){
                getline(fileIn, temp);
                if (!(getWord(temp, 1) == "")){
                    if (!(getWord(temp,2) == "")){
                        text[i] = temp;
                        if (int(text[i].find(":")) >= 0){
                            for (int j = 0; j <= int(text[i].find(":")); j++){
                                text[i][j] = ' ';
                            }
                        }
                        i++;
                    }
                }
            }
            numberOfInstruction = i;
            break;
        }
    }
// This is for LABEL part
    fileIn.seekg(0);
    string offsetLine = "";
    while(1) {
        getline(fileIn, offsetLine);
        string label = getWord(offsetLine, 1);
        if(!label.compare(".text")) break;
    }
    int countAddress = 0;
    while(!fileIn.eof()) {
        getline(fileIn, offsetLine);
        string word1 = getWord(offsetLine, 1);
        if((int)offsetLine.find(":") == -1 && word1.compare("")) countAddress++;
        if((int)offsetLine.find(":") != -1) {

            string label = getWord(offsetLine, 1);
            if(labelArray == nullptr) {
                labelArray = new Label;
                labelArray->labelName = label;
                labelArray->labelAddress = countAddress * 4;
            }
            else {
                Label* seeker = labelArray;
                while(seeker != nullptr) {
                    if(seeker->next == nullptr) {
                        seeker->next = new Label;
                        seeker->next->labelName = label;
                        seeker->next->labelAddress = countAddress * 4;
                        break;
                    }
                    seeker = seeker->next;
                }
            }
            string word2 = getWord(offsetLine, 2);
            if(word2.compare("")) countAddress++;
        }
    }
    Label* seeker = labelArray;
    while(seeker != nullptr) {
        if(seeker->labelAddress > (countAddress - 1) * 4) seeker->labelAddress = -1;
        seeker = seeker->next;
    }
    fileIn.close();
};
string FileAssembly::getInstruction(int address){
	if (address % 4 != 0) return "";
	if (address/4 < numberOfInstruction) return text[address/4];
	else return "";
}
int FileAssembly::getLabelAddress(string _label) {
    Label* seeker = labelArray;
    while(seeker != nullptr){
        if(!seeker->labelName.compare(_label)) return seeker->labelAddress;
        seeker = seeker->next; 
    }
    return -1;
}
// int main(){
// 	FileAssembly input("assembly.txt");
// }
#endif