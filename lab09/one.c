// Lab 09 - One
// Authors: Nathan Ellis & Serena Thai
// Date: 7 May 2017

#include <stdio.h>

#define MAX_LENGTH 4096

int main (void) {
	char str[MAX_LENGTH];

	printf("Enter a string: ");
	fgets(str, MAX_LENGTH, stdin);

	for (int i = 0; str[i] != '\n'; i++) {
		printf("%c\n", str[i]);		
	}

	return 0;
}
