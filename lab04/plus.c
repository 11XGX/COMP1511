#include <stdio.h>
#include <math.h>

int main (void) {
	int row, col, num;

	printf("Enter size: ");
	scanf("%d", &num);
	row = 1;
	float middle = floorf(num / 2 + 2);
	
	while (row <= num) {
	col = 2;		
		while (col <= num){
			if (col == middle) {
				printf("*");
			} 
			
			if (row + 1== middle) {
				printf("*");
			}
			
			else {
				printf("-");
			}
			
		col++;
		}
		
	printf("\n");
	row++;
	}

	return 0;
}
