#ifndef GET_WORD
#define GET_WORD

#include <string>
#include <sstream>
using namespace std;
string getWord(string _name, int n) {
    int count = 0;
    while (_name[count] != '\0') {
        if (_name[count] == ',' || _name[count] == ':' || _name[count] == '\'') _name[count] = ' ';
        count ++;
    }
    stringstream nameStream(_name);
    string getName;
    int i = 0;
    while (nameStream >> getName) {
        i++;
        if (i==n) return getName;
    } 
    return "";
}
string optimizeString(string instruction){
    // char output[100];
	// int i = 0, j = 0;
	// while (instruction[i] == ' ') i++;
	// if ((instruction[i] == '\t') || (instruction[i] == '\n')) i++;
	// while (instruction[i] != '\0') {
	// 	output[j] = instruction[i];
	// 	if (instruction[i] == ' ') {
	// 		if (output[j - 1] == ')') j--;
	// 		if ((instruction[i - 1] == ' ') || (instruction[i + 1] == ')')) { i++; continue; }
	// 		if ((instruction[i + 1] == '(') && (output[j - 1] = ',')) { i++; j++; continue; }
	// 		if ((instruction[i + 1] == '(') || (instruction[i - 1] >= 48) && (instruction[i - 1] <= 57)) j--;
	// 	}
	// 	if ((instruction[i] == ',') && (instruction[i + 1] != ' ')) {
	// 		j++;
	// 		output[j] = ' ';
	// 	}
	// 	if (i>= 2) if ((output[j - 2] == '(') && (output[j - 1] == ' ')) {
	// 			i--;
	// 			j--;
	// 			continue;
	// 	}
	// 	j++;
	// 	i++;
	// }
	// output[j] = '\0';
	// return output;
	int wordOffset = 1;
	string output;
	while(getWord(instruction, wordOffset).compare("")) {
		output.append(getWord(instruction, wordOffset));
		output.append(" ");
		wordOffset++;
	}
	return output;
}
#endif
