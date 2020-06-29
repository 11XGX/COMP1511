// This program was created by Nathan Ellis.
// Date: 15/03/2017
// This program calculates all the leap years which lie within a given range.

#include <stdio.h>

int main (void) {
	int startYear, finishYear;
	
	printf("Enter start year: "); 
	scanf("%d", &startYear);
	printf("Enter finish year: ");
	scanf("%d", &finishYear);
	
	printf("The leap years between %d and %d are: ", startYear, finishYear);
	while (startYear <= finishYear) {
		if (startYear % 4 == 0 && ((startYear % 100 != 0) || (startYear % 400 == 0))) {
			printf("%d ", startYear);
		}
		
		startYear++;
	}
	
	printf(" \n");
	
	return 0;
}
