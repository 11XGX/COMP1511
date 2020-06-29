// Date: 15/03/2017
// Authors: Isaac Ronthal & Nathan Ellis
// This is a program which makes squares of a chosen size.

#include <stdio.h>

int main (void) {
	int num, row;
	
	printf("Square size: ");
	scanf("%d", &num);
	row = 1;

	while (i <= num*num){		
		if (row % n == 0) {
			printf("*\n");
		} else {
			printf("*");
		}
		i++;
	}

	printf("");

	return 0;
}
