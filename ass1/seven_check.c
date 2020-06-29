// Author: Nathan Ellis
// Date: 30 April 2017
// Seven Check - This function completes searches to discern if the given digit is a 7.

#include <stdio.h>
#include "captcha.h"

int get_seven_check(int height, int width, int pixels[height][width]) {
	int regular_thickness = 0, check_thickness = 0;
	
	// Calculate the thickness of the line in the middle row
	for (int column = 0; column < width; column++) {
		if (pixels[height/2][column] == 1) {
			regular_thickness++;
		}
	}
	
	// Check that all values from middle row down to the bottom of the image have approximately the same thickness to the base of the image
	for (int row = (height/2); row > 1; row--) {
		check_thickness = 0;
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 1) {
				check_thickness++;
			}
			if (column == width - 1) {
				if ((regular_thickness > check_thickness + 15) || (regular_thickness < check_thickness - 5)) {
					return 0;
				}
			}
		}
	}
	
	return 1;
}
