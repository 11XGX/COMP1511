// Author: Nathan Ellis
// Date: 30 April 2017
// Five Check - This function completes searches to discern if the given digit is a 5.

#include <stdio.h>
#include "captcha.h"

int get_five_check(int height, int width, int pixels[height][width]) {
	int last_black_column[20] = {0}, i = 0;
	
	// This searches for the locations of the last black pixels found in each row, searching right to left from the top-right of the digit.
	for (int row = height - 2; row > (height - 22); row--) {
		for (int column = width - 1; column > -1; column--) {
			if (pixels[row][column] == 1) {
				last_black_column[i] = column;
				i++;
				break;
			}
		}
	}
	
	/*for (int i = 0; i < 17; i++) {
		printf("Last Black Column = %d\n", last_black_column[i]);
	}*/
	
	// If there is a significant change between one value and the row below, the check is true. 
	for (int i = 0; i < 18; i++) {
		if (last_black_column[i] > last_black_column[i + 2] + 5) {
			return 1;
		} else if (last_black_column[i] > last_black_column[i + 1] + 5) {
			return 1;
		} else if (last_black_column[i] < last_black_column[i + 2] - 11) {
			return 1;
		} else if (last_black_column[i] < last_black_column[i + 1] - 11) {
			return 1;
		}
	}
	
	return 0;
}
