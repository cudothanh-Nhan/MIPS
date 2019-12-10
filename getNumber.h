#ifndef GETNUMBER
#define GETNUMBER
#include <iostream>
#include <math.h>
#include <string>

int getNumbers(string _instruction) {
	string imm = "";
	int num = 0;
	int index = 0;
	int count = 0;
	bool dau = false;
	bool hexa = false;
	while (1) {
		if (((int(_instruction[index]) >= 48)) && (int(_instruction[index] <= 57))) {
			if ((_instruction[index - 1] == ' ') || (_instruction[index - 1] == ',') || (_instruction[index - 1] == '-')) {
				if (_instruction[index - 1] == '-') dau = true;
				while (1) {
					if (_instruction[index+count + 1] == 'x'){
						while (_instruction[index + count] != '\0'){
							imm += (_instruction[index + count]);
							count++;
						}
						hexa = true;
						break;
					}
					imm  += _instruction[index + count];
					count++;
					if ((_instruction[index + count] == '\0') || (_instruction[index + count] == ' ') 
                    || (_instruction[index + count] == '(') || (_instruction[index + count] == ')')) break;
				}
			}
		}
		if ((count > 0) || (_instruction[index + 1] == '\0')) break;
		index++;
	}
	if(!imm.compare("")) return 0;
	else if (hexa == true) return stoi(imm, 0, 16);
	else return stoi(imm);
}
#endif