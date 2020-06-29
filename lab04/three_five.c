#include <stdio.h>

int main (void) {
	int i, n;
	i = 3;
	
	printf("Enter number: ");
	scanf("%d", &n);
	
	while (i < n) {
		if (i % 3 == 0 | i % 5 == 0) {
			printf("%d\n", i);
		}
		i++;
	}

	return 0;
}
