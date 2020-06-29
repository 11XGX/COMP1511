#include <stdio.h>

int main (void) {
	int row, col, num, start, end;

	printf("Enter size: ");
	scanf("%d", &num);
	row = 1;

	start = 1;
	end = num;

	while (row <= num) {
	col = 1;
		while (col <= num){
			if (col == start || col == end) {
				printf("*");
			} else {
				printf("-");
			}
		col++;
		}
	printf("\n");
	
	start++;
	end--;
	row++;
	}

	return 0;
}
