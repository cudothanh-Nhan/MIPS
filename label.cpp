#include <iostream>
#include <string>
#include <fstream>
#include "getWord.h"
using namespace std;

class FileAssembly {
protected:
    string linkFile;
    struct Label {
        string labelName;
        int labelAddress = -1;
        Label* next = nullptr;
    };
    Label* labelArray = nullptr;
public:
    void method(){};
    FileAssembly(string _linkFile) : linkFile(_linkFile) {
        ifstream fileIn;
        fileIn.open(linkFile);
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
        // Label* seeker = labelArray;
        // while(seeker != nullptr) {
        //     if(seeker->labelAddress > (countAddress - 1) * 4) seeker->labelAddress = -1;
        //     seeker = seeker->next;
        // }
        // seeker = labelArray;
        // while(seeker != nullptr) {
        //     cout << seeker->labelName << ' ' << seeker->labelAddress << '\n';
        //     seeker = seeker->next;
        // }
        // cout << "Done";
    }
    
};
int main() {
    FileAssembly input("assembly.txt");
    return 0;
}