#include <stdio.h>

int main (void) {
	int a, b, c, min, middle, max;
	min = 0;
	middle = 0;
	max = 0;

	printf("Enter integer: ");
	scanf("%d", &a);
	printf("Enter integer: ");
	scanf("%d", &b);
	printf("Enter integer: ");
	scanf("%d", &c);

	min = a;
	min > b && min == b;
	min > c && min == c;
	printf("%d", min);

	middle = b;
	b < max && b > min && middle == b;
	c < max && c > min && middle == c;
	printf("%d", middle);

	max = c;
	max < b && max == b;
	max > c && max == c;
	printf("%d");

	printf("\n");

	return 0;
}
