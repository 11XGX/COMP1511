#include <stdio.h>
#include "captcha.h"

int get_max_vertical_intersections(int height, int width, int pixels[height][width]) {
	// Flag used to deduce whether the function is intersecting a line
	int intersecting = 0;
	// Measure how many intersections are in each column
	int intersections = 0;
	// Maximum value of intersections
	int max_intersections = 0;
	
	for (int column = 2; column < width - 2; column++) {
		for (int row = 0; row < height; row++) {
			// There are three conditions to test how many intersections are in each column
			if (pixels[row][column] == 1 && pixels[row][column + 1] == 1 && pixels[row][column - 1] == 1 && intersecting == 0) {
				intersecting = 1;
			}
			if (pixels[row][column] == 0 && pixels[row][column + 1] == 0 && pixels[row][column - 1] == 0 && intersecting == 1) {
				intersecting = 0;
				intersections++;
			}
			if (intersecting == 1 && row == height - 1) {
				intersections++;
			}
		}
		
		if (intersections > max_intersections) {
			max_intersections = intersections;
		}
		
		intersections = 0;
		intersecting = 0;
	}
	
	return max_intersections;
	
}
