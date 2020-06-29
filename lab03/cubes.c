// Date: 15/03/2017
// Authors: Nathan Ellis & Isaac Ronthal
// This is a program which calculates the cubes up to a given integer.

#include <stdio.h>

int main (void) {
	int num, i, cube;
	i = 1;
	
	printf("Enter how many cubes: ");
	scanf("%d", &num);
	
	while (i <= num) {
		cube = i*i*i;
		printf("%d^3 = %d\n", i, cube); 
		i++;
	}

	return 0;
}
