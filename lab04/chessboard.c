#include <stdio.h>

int main (void) {
	int num, row, col;
	num = 1;
	row = 1;
	
	
	printf("Enter size: ");
	scanf("%d", &num);
	
	while (row <= num) {
		col = 1;	
		while (col <= num) {
			if (row % 2 == 0 && col % 2 == 0) {
				printf("-");
			} else if (row % 2 != 0 && col % 2 != 0) {
				printf("-");
			} else {
				printf("*");
			}
			col++;
		}
		row++;
		printf("\n");
	}
	
	return 0;
}
