#include <stdio.h>

int main (void) {
	int i, num, sum;
	i = 1;
	sum = 0;

	printf("Enter number: ");
	scanf("%d", &num);

	printf("The factors of %d are:\n", num);

	while (i <= num) {
		if (num % i == 0) {
			printf("%d\n", i);
			sum = sum + i;
		}
		i++;
	}

	printf("Sum of factors = %d\n", sum);

	if (num == sum / 2) {
		printf("%d is a perfect number\n", num);
	} else {
		printf("%d is not a perfect number\n", num);
	}

	return 0;
}
