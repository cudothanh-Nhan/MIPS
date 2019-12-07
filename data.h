#ifndef DATA
#define DATA

#include <iostream>
#include <fstream>
#include <string>
#include "getWord.h"

using namespace std;

class FileAssembly {
protected:
    struct Data {
        string name;
        string type;
        void* ptrData ;
        Data* next = nullptr;
    };
    string linkFile;
    Data* root = nullptr;
public:
    FileAssembly(string _linkFile) : linkFile(_linkFile) {
        ifstream fileIn;
        fileIn.open(_linkFile);
        string stringLine;
        getline(fileIn, stringLine);
        
        while(!fileIn.eof()) {
            getline(fileIn,stringLine);
            if (!stringLine.compare(".text")) break;
            
            int countArray = 1;
            for (int i = 3; i <= 50; i++) {
                if (!getWord(stringLine,i).compare("")) break;
                countArray++;
            }
            
            Data* temp = root;
            root = new Data;
            
            root->name = getWord(stringLine,1);
            root->type = getWord(stringLine,2);
            int countPtr = 0;

            if (!getWord(stringLine,2).compare(".word") ) root->ptrData = (void*)(new int[countArray]);
            else if (!getWord(stringLine,2).compare(".float")) root->ptrData = (void*)(new float[countArray]);
            else if (!getWord(stringLine,2).compare(".double")) root->ptrData = (void*)(new double[countArray]);
            else if (!getWord(stringLine,2).compare(".byte") || !getWord(stringLine,2).compare(".asciiz")) root->ptrData = (void*)(new string[countArray]);
            
            for (int i = 3 ; i <= 50 ; i++) {
                if (!getWord(stringLine,i).compare("")) break;

                if (!getWord(stringLine,2).compare(".word") ) {
                    *((int*)root->ptrData + countPtr) = stoi(getWord(stringLine,i));
                    countPtr++;
                }
                else if (!getWord(stringLine,2).compare(".float")) {
                    *((float*)root->ptrData + countPtr) = stof(getWord(stringLine,i));
                    countPtr++;
                }
                else if (!getWord(stringLine,2).compare(".double")) {
                    *((double*)root->ptrData + countPtr) = stod(getWord(stringLine,i));
                    countPtr++;
                }
                else if (!getWord(stringLine,2).compare(".byte") || !getWord(stringLine,2).compare(".asciiz")) {
                    *((string*)root->ptrData + countPtr) = getWord(stringLine,i);
                    countPtr++;
                } 
            }
            root->next = temp;
        } 
    }
    void* getDataAddress(string);
    ~FileAssembly();
};

void* FileAssembly::getDataAddress(string _name) {
    Data* seeker = root;
    while (seeker != nullptr) {
        if (!seeker->name.compare(_name)) return seeker->ptrData;
        seeker = seeker->next;
    }
}
FileAssembly::~FileAssembly() {
    Data* seeker = root;
    while (seeker != nullptr) {
        if (!seeker->type.compare(".word")) {
            delete[] (int*)seeker->ptrData;
        }
        else if (!seeker->type.compare(".float")) {
            delete[] (float*)seeker->ptrData;
        }
        else if (!seeker->type.compare(".double")) {
            delete[] (double*)seeker->ptrData;
        }
        else if (!seeker->type.compare(".byte") || !seeker->type.compare(".asciiz")) {
            delete[] (string*)seeker->ptrData;
        }
        seeker = seeker->next;
    }
}

#endif