// Author: Nathan Ellis
// Date: 30 April 2017
// Vertical Balance - This function uses an algorithm to find the balance of an image vertically (the balance of black pixels).

#include <stdio.h>
#include "captcha.h"

double get_vertical_balance(int height, int width, int pixels[height][width]) {
	double row_sum = 0;
	int row = width;
	int i = 0, j = 0, n_black_pixels = 0;
	
	// Scan the image for the locations of black pixels and increase a total in row sum.
	while (i < height) {
		j = 0;
		while (j < width) {
			if (pixels[i][j] == 1) {
				n_black_pixels++;
				row_sum = row_sum + i;
			}
			j++;
		}
		i++;
	}
	
	// Return the value between 0 to 1, indicating the digit's vertical blanace.
	return ((row_sum/n_black_pixels) + 0.5)/height;
	
}
