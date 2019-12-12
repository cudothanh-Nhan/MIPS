#ifndef GET_REGISTER
#define GET_REGISTER
#include <string>
using namespace std;
string getRegister(string _str, int number) {
    int countRegister = 0;
    string word = "";
    for(int i = 0; i <= _str.length() + 1; i++) {
        if(_str[i] == '\0') break;
        if(_str[i] == '$') {
            countRegister++;
        }
        if(countRegister == number) {         
            while(_str[i] != ' ' && _str[i] != ',' && _str[i] != '\0' && _str[i] != ')' && _str[i] != '(' && _str[i] != '\t') {
                word += _str[i];
                i++;
            }
            break;
        }
    }
    return word; 
}
#endif