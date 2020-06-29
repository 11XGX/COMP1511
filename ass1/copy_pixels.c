// Author: Nathan Ellis
// Date: 30 April 2017
// Copy Pixels - This function uses a given height and width and copies a certain section of the array given by the bounding_box function.

#include <stdio.h>
#include "captcha.h"

void copy_pixels(int height, int width, int pixels[height][width], int start_row, int start_column, int copy_height, int copy_width, int copy[copy_height][copy_width]) {
	int i = 0, j = 0;

	// These nested loops scan for the binary values of each position within the bounded section of the pixels array.
	while (i < copy_height) {
		j = 0;
		while (j < copy_width) {
			copy[i][j] = pixels[start_row + i][start_column + j];
			j++;
		}
		i++;
	}

}
