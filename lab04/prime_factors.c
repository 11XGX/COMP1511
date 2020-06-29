#include <stdio.h>

int main (void) {
	int i, num, n;	
	i = 2;
	
	printf("Enter number: ");
	scanf("%d", &num);
	
	n = num;
	
	while (i <= n/2 && n != 1) {
		if (n == num && n % i == 0) {
			printf("The prime factorization of %d is:\n", num);
		} if (n % i == 0) {
			n = n / i;
			printf("%d * ", i);
		} else {
			i++;
		}
	}
	
	if (n >= 2 && n < num) {
		printf("%d = %d\n", n, num);
	}
	if (n == num) {
		printf("%d is prime\n", num);
	}
	
	return 0;
}
