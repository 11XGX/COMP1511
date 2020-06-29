// Author: Nathan Ellis
// Date: 30 April 2017
// Three Check - This function completes searches to discern if the given digit is a 3. 

#include <stdio.h>
#include "captcha.h"

int get_three_check1(int height, int width, int pixels[height][width]) {
	int first_black_column[25] = {0}, i = 0;
	
	// This searches for the locations of the first black pixels found in each row, searching left to right from the bottom-left of the digit.
	for (int row = 0; row < 25; row++) {
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 1) {
				first_black_column[i] = column;
				i++;
				break;
			}
		}
	}
	
	/*for (int i = 0; i < 25; i++) {
		printf("First Black Column = %d\n", first_black_column[i]);
	}*/
	
	// If there is a significant change between one value and the row above, the check is true. 
	for (int i = 1; i < 25; i++) {
		if (first_black_column[i] > first_black_column[i - 1] + 9) {
			return 1;
		} else if (first_black_column[i] < first_black_column[i - 1] - 9) {
			return 1;
		}
	}
	
	return 0;
}

int get_three_check2(int height, int width, int pixels[height][width]) {
	int last_black_column[15] = {0}, i = 0;
	
	// This searches for the locations of the last black pixels found in each row, searching right to left from the bottom-right of the digit.
	for (int row = 0; row < 15; row++) {
		for (int column = width - 1; column > -1; column--) {
			if (pixels[row][column] == 1) {
				last_black_column[i] = column;
				i++;
				break;
			}
		}
	}
	
	/*for (int i = 0; i < 10; i++) {
		printf("Last Black Column = %d\n", last_black_column[i]);
	}*/
	
	// If there is a significant change between one value and the row above, the check is true. 
	for (int i = 1; i < 15; i++) {
		if (last_black_column[i] > last_black_column[i - 1] + 10) {
			return 0;
		} else if (last_black_column[i] < last_black_column[i - 1] - 10) {
			return 0;
		}
	}
	
	return 1;
}
