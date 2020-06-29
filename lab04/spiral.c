#include <stdio.h>

int main (void) {
	int num, row, col, n, i;
	row = 1;
	i = 0;
	
	
	printf("Enter size: ");
	scanf("%d", &num);
	
	n = num;
	
	while (row <= num) {
	col = 1;	
		while (col <= num) {
			if (row == 1 || row == n) {
				printf("*");
			} else if (col == n) {
				printf("*");
			} else if (col == 1 && row >= n-i) {
				printf("*");
			}

			else {
				printf("_");
			}
			col++;
		}
		row++;
		printf("\n");
	}
	printf("\n");
	
	return 0;
}
