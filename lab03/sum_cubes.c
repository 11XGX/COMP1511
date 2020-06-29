#include <stdio.h>

int main (void) {
	int num, i, cube, sum;
	i = 1;
	sum = 1;
	
	printf("Sum how many cubes? ");
	scanf("%d", &num);

	printf("%d^3 ", i);

	while (i < num) {
		i++;		
		cube = i*i*i;
		printf("+ %d^3 ", i); 
		sum = sum + cube;
	}

	i++;
	printf("= %d\n", sum);

	return 0;
}
