// Author: Nathan Ellis
// Date: 30 April 2017
// One Check - This function completes searches to discern if the given digit is a 1.

#include <stdio.h>
#include "captcha.h"

int get_one_check(int height, int width, int pixels[height][width]) {
	int first_black_column[12];
	
	// This searches for the locations of the first black pixels found in each row, searching left to right from the bottom_left of the digit. 
	for (int row = 0; row < 12; row++) {
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 1) {
				first_black_column[row] = column;
				break;
			}
		}
	}
	
	/*for (int i = 0; i < 10; i++) {
		printf("First Black Column = %d\n", first_black_column[i]);
	}*/
	
	// If there is a significant change between one value and the row above, the check is true. 
	for (int i = 0; i < 11; i++) {
		if (first_black_column[i] < first_black_column[i + 1] - 6) {
			return 1;
		}
	}
	
	return 0;
}
