// Author: Nathan Ellis
// Date: 30 April 2017
// Horizontal Balance - This function uses an algorithm to find the balance of an image horizontally (the balance of black pixels).

#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]) {
	double column_sum = 0;
	int i = 0, j = 0, n_black_pixels = 0;
	
	// Scan the image for the locations of black pixels and increase a total in column sum.
	while (i < height) {
		j = 0;
		while (j < width) {
			if (pixels[i][j] == 1) {
				n_black_pixels++;
				column_sum = column_sum + j;
			}
			j++;
		}
		i++;
	}
	
	// Return the value between 0 to 1, indicating the digit's horizontal blanace.
	return ((column_sum/n_black_pixels) + 0.5)/width;
	
}
