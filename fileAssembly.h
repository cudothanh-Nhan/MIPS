#ifndef GETTEXT
#define GETTEXT

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "getWord.h"	
using namespace std;

class FileAssembly {
protected:
    struct Label {
        string labelName;
        int labelAddress = -1;
        FileAssembly::Label* next = nullptr;
    };
    struct Data {
        string name;
        string type;
        void* ptrData ;
        Data* next = nullptr;
    };
	string linkFile;
	string text[1000];
	int numberOfInstruction = 0;
    FileAssembly::Label* labelRoot = nullptr;
    Data* dataRoot = nullptr;
public:
    FileAssembly(){};
    void loadLink (string _linkFile);
	string getInstruction(int);
    int getLabelAddress(string);
    void* getDataAddress(string);
    ~FileAssembly();
};
void FileAssembly::loadLink(string _linkFile) {
// This is for TEXT PART
    linkFile = _linkFile;
    int i = 0;
    string temp;
    ifstream fileIn;
    fileIn.open(_linkFile, ios::binary);
    while (!fileIn.eof()){
        getline(fileIn, temp);
        if (int(temp.find(".text")) >= 0){
            while (!fileIn.eof()){
                getline(fileIn, temp);
                if (!(getWord(temp, 1) == "")){
                    if (!(getWord(temp,2) == "") || !(getWord(temp, 1).compare("syscall"))){
                        text[i] = temp;
                        if (int(text[i].find("#")) >= 0){
                                int j = (int)(text[i].find("#"));
								while (text[i][j] !=  '\0'){
                                    text[i][j] = ' ';
                                    j++;
                                }
							}
                        if (int(text[i].find(":")) >= 0){
                            for (int j = 0; j <= int(text[i].find(":")); j++){
                                text[i][j] = ' ';
                            }
                        }
                        if (getWord(text[i], 1) != "") i++;
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

        if((int)offsetLine.find(":") == -1 && word1.compare("") && word1.find("#") == -1) countAddress++;
        if((int)offsetLine.find(":") != -1 && word1.find("#") == -1) {

            string label = getWord(offsetLine, 1);
            if(labelRoot == nullptr) {
                labelRoot = new Label;
                labelRoot->labelName = label;
                labelRoot->labelAddress = countAddress * 4;
            }
            else {
                Label* seeker = labelRoot;
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
            if(word2.compare("") && word2.find("#") == -1) countAddress++;
        }
    }
    Label* seeker = labelRoot;
    while(seeker != nullptr) {
        if(seeker->labelAddress > (countAddress - 1) * 4) seeker->labelAddress = -1;
        seeker = seeker->next;
    }

// This is for DATA Part
    fileIn.seekg(0);
    string stringLine;
    while(1) {
        getline(fileIn, stringLine);
        stringLine = getWord(stringLine, 1);
        if(!stringLine.compare(".data")) break;
    }
    while(!fileIn.eof()) {

        getline(fileIn,stringLine);
        string test = getWord(stringLine,1);
        if (!test.compare(".text")) break;
        
        int countArray = 1;
        for (int i = 3; i <= 500; i++) {
            if (!getWord(stringLine,i).compare("")) break;
            countArray++;
        }
        Data* temp = dataRoot;
        dataRoot = new Data;
        
        dataRoot->name = getWord(stringLine,1);
        dataRoot->type = getWord(stringLine,2);
        int countPtr = 0;
        if (!getWord(stringLine,2).compare(".word") ) dataRoot->ptrData = (void*)(new int[countArray]);
        else if (!getWord(stringLine,2).compare(".float")) dataRoot->ptrData = (void*)(new float[countArray]);
        else if (!getWord(stringLine,2).compare(".double")) dataRoot->ptrData = (void*)(new double[countArray]);
        else if (!getWord(stringLine,2).compare(".asciiz")) ;
        else if (!getWord(stringLine,2).compare(".byte")) dataRoot->ptrData = (void*)(new char[countArray]);
        
        for (int i = 3 ; i <= 500 ; i++) {
            if (!getWord(stringLine,i).compare("")) break;

            if (!getWord(stringLine,2).compare(".word") ) {
                *((int*)dataRoot->ptrData + countPtr) = stoi(getWord(stringLine,i));
                countPtr++;
            }
            else if (!getWord(stringLine,2).compare(".float")) {
                *((float*)dataRoot->ptrData + countPtr) = stof(getWord(stringLine,i));
                countPtr++;
            }
            else if (!getWord(stringLine,2).compare(".double")) {
                *((double*)dataRoot->ptrData + countPtr) = stod(getWord(stringLine,i));
                countPtr++;
            }
            else if (!getWord(stringLine,2).compare(".asciiz")) {
                int countString = 0;
                while (1) {
                    if (stringLine[countString] == '\"') break;
                    countString++;
                }
                countString++;
                string stringIn = "";
                while (1) {
                    if (stringLine[countString] == '\"') break;
                    stringIn += stringLine[countString];
                    countString++;
                }
                countString++;
                int count = 0;
                while (stringIn[count] != '\0') {
                    if ( stringIn[count] == '\\' && stringIn[count+1] == 'n') {
                        stringIn[count] = '\n';
                        stringIn.erase(stringIn.begin() + (count + 1));
                    }
                    else if ( stringIn[count] == '\\' && stringIn[count+1] == 't') {
                        stringIn[count] = '\t';
                        stringIn.erase(stringIn.begin() + (count + 1));
                    }
                    count++;        
                }
                char* temp = new char[count + 1];
                int offset = 0;
                while(stringIn[offset] != '\0') {
                   *(temp + offset) = stringIn[offset];
                   offset++; 
                }
                *(temp + offset) = '\0';
                dataRoot->ptrData = temp;
            }
            else if(!getWord(stringLine,2).compare(".byte")) {
                *((char*)dataRoot->ptrData + countPtr) = getWord(stringLine,i)[0];
                countPtr++;
            } 
        }
        dataRoot->next = temp;
    } 
    fileIn.close();
};
string FileAssembly::getInstruction(int address){
	if (address % 4 != 0 || address < 0) return "";
	if (address/4 < numberOfInstruction) return text[address/4];
	else return "";
}
int FileAssembly::getLabelAddress(string _label) {
    _label = getWord(_label, 1);
    Label* seeker = labelRoot;
    while(seeker != nullptr){
        if(!seeker->labelName.compare(_label)) return seeker->labelAddress;
        seeker = seeker->next; 
    }
    return -1;
}
void* FileAssembly::getDataAddress(string _name) {
    _name = getWord(_name, 1);
    Data* seeker = dataRoot;
    while (seeker != nullptr) {
        cout << seeker->name << ' ' ;
        if (!seeker->name.compare(_name)) {
            cout << "data" <<'\n';
            //if(!seeker->type.compare(".asciiz")) return (void*)((char*)seeker->ptrData + 8) ;
            return seeker->ptrData;
        }
        seeker = seeker->next;
    }
    return nullptr;
}
FileAssembly::~FileAssembly() {
    Data* seeker1 = dataRoot;
    while (seeker1 != nullptr) {
        if (!seeker1->type.compare(".word")) {
            delete[] (int*)seeker1->ptrData;
        }
        else if (!seeker1->type.compare(".float")) {
            delete[] (float*)seeker1->ptrData;
        }
        else if (!seeker1->type.compare(".double")) {
            delete[] (double*)seeker1->ptrData;
        }
        else if (!seeker1->type.compare(".asciiz")) {
            delete[] (char*)seeker1->ptrData;
        }
        else if (!seeker1->type.compare(".byte")) {
            delete[] (char*)seeker1->ptrData;
        }
        Data* temp = seeker1;
        seeker1 = seeker1->next;
        delete temp;
    }
    Label* seeker2 = labelRoot;
    while(seeker2 != nullptr) {
        Label* temp = seeker2;
        seeker2 = seeker2->next;
        delete temp;
    }
}
// int main(){
// 	FileAssembly input("assembly.txt");
// }
#endif