// C++ program to demonstrate working of regex_search() 
#include <iostream> 
#include "register.h"
#include<string.h> 
using namespace std; 
Register reg("registerList.txt");
int main() 
{ 
    reg.init();
    reg.setRegisterValue("lo", 10);
    cout << reg.getRegisterValue("lo");
} 