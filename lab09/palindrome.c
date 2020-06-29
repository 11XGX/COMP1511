// Lab 09 - Palindrome
// Authors: Nathan Ellis & Serena Thai
// Date: 7 May 2017

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 4096

int main(void) {
	char str[MAX_LENGTH];
	int maxElementPosition, finished = 0;

	printf("Enter a string: ");
	fgets(str, MAX_LENGTH, stdin);

	//Find last non-null element
	maxElementPosition = strlen(str);

	//printf("%d\n", maxElementPosition);

	for (int i = 0; i < maxElementPosition/2; i++) {
		if (str[i] != str[maxElementPosition - 2]) {			
			printf("String is not a palindrome\n");
			finished = 1;
			break;
		}

		maxElementPosition--;
	}

	if (finished == 0) {
		printf("String is a palindrome\n");
	}

	return 0;
}
