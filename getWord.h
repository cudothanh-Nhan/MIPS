#ifndef GET_WORD
#define GET_WORD

#include <string>
#include <sstream>

using namespace std;
string getWord(string _name, int n) {
    int count = 0;
    while (_name[count] != '\0') {
        if (_name[count] == ',' || _name[count] == ':' ) _name[count] = ' ';
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
#endif