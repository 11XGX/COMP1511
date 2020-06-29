// Author: Nathan Ellis
// Date: 30 April 2017
// Four Check - This function completes searches to discern if the given digit is a 4.

#include <stdio.h>
#include "captcha.h"

int get_four_check(int height, int width, int pixels[height][width]) {
	// This checks for the presence of a black pixel in the top-left of the digit image.
	for (int row = height - 1; row > height - 8; row--) {
		for (int column = 0; column < 7; column++) {
			if (pixels[row][column] == 1) {
				return 0;
			}
		}
	}
	
	// This checks for the presence of a black pixel in the bottom-left of the digit image.
	for (int row = 0; row < 2; row++) {
		for (int column = 0; column < 5; column++) {
			if (pixels[row][column] == 1) {
				return 0;
			}
		}
	}
	
	// This checks for the presence of a black pixel in the middle-right of the digit image.
	for (int row = (height/2); row < (height/2) + 4; row++) {
		for (int column = width - 1; column > width - 4; column--) {
			if (pixels[row][column] == 1) {
				return 0;
			}
		}
	}
	
	return 1;
}
