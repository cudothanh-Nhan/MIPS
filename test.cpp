#include <iostream>
#include <iostream>
#include "register.h"
#include "Serial.h"
using namespace std;

int main() {
    Serial cmd;
    cmd.init();
    cmd.pause();
    if(cmd.write("$ra", 100) == 1){
        cmd.init();
    }
    cmd.pause();
    if(cmd.write("$fp", 100) == 1){
        cmd.init();
    }
    cmd.pause();
    if(cmd.write("$ra", 100) == 1){
        cmd.init();
    }  
}