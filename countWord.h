#ifndef COUNTWORD
#define COUNTWORD
int countWord(string input) {
	int i = 0, count = 0, length = 0;
	while (input[length] != '\0') length++;
	while (i <= length) {
		if (input[i] == ',') count++;
		else if (input[i] == ' ') {
			if ((input[i - 1] == ',') && (input[i - 2] != ' ')) count--;
			while (input[i] == ' ') i++;
			if ((input[i] != ',') && (i < length)) count++;
			if ((input[i] == ',') && (input[i-1] != ' ')) i--;
		}
	i++;
	}
	return count + 1;
}
#endif