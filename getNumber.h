#ifndef GETNUMBER
#define GETNUMBER
#include <iostream>
#include <math.h>
#include <string.h>

int getNumbers(string _instruction) {
	char imm[100];
	int num = 0;
	int index = 0;
	int count = 0;
	bool dau = false;
	while (1) {
		if (((int(_instruction[index]) >= 48)) && (int(_instruction[index] <= 57))) {
			if ((_instruction[index - 1] == ' ') || (_instruction[index - 1] == ',') || (_instruction[index - 1] == '-')) {
				if (_instruction[index - 1] == '-') dau = true;
				while (1) {
					imm[count] = _instruction[index + count];
					count++;
					if ((_instruction[index + count] == '\0') || (_instruction[index + count] == ' ') 
                    || (_instruction[index + count] == '(') || (_instruction[index + count] == ')')) break;
				}
			}
		}

		if ((count > 0) || (_instruction[index + 1] == '\0')) break;

		index++;
	}
	for (int i = count - 1; i >= 0; i--) {
			num += (int(imm[i]) - 48) * pow(10, count - i - 1);
	}
	if (dau == true) num = -num;
	return num;
}
#endif