#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include "getWord.h"
using namespace std;

class FileAssembly {
	string linkFile;
	string text[100];
	int numberOfInstruction = 0;
public:
	FileAssembly(string _linkFile) : linkFile(_linkFile){
		int i = 0;
		string temp;
		ifstream fileIn;
		fileIn.open(_linkFile);
		while (!fileIn.eof()){
			getline(fileIn, temp);
			if (int(temp.find(".text")) >= 0){
				while (!fileIn.eof()){
					getline(fileIn, temp);
                    if (!((getWord(temp, 1) == "") || (getWord(temp,2) == ""))){
                        text[i] = temp;
                        if (int(text[i].find(":")) != 0){
                            for (int j = 0; j <= i; j++){
                                text[i][j] = ' ';
                            }
                        }
                        i++;
                    }
				}
				numberOfInstruction = i;
				break;
			}
		}
		fileIn.close();
	};
	string getInstruction(int);
};
string FileAssembly::getInstruction(int address){
	if (address % 4 != 0) return "Nhap sai dia chi";
	if (address/4 < numberOfInstruction) return text[address/4];
	else return "DEO CO DAU MA KIEM";
}
int main(){
	FileAssembly input("assembly.txt");
	int t;
	cin >> t;
	cout << input.getInstruction(t);
	return 0;
}