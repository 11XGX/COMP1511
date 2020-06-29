// Author: Nathan Ellis
// Date: 30 April 2017
// Bottom Hole Location - This function uses a four-pass flood-fill algorithm to isolate holes and then checks for the value of the lowest row position of the hole.

#include <stdio.h>
#include <math.h>
#include "captcha.h"

int get_bottom_hole_location(int height, int width, int pixels[height][width]) {
	// Set the border values of the array equal to 2 (as there are no holes present).
	for (int row = 0; row < height; row++) {
		pixels[row][0] = 2;
	}
	
	for (int row = 0; row < height; row++) {
		pixels[row][width-1] = 2;
	}
	
	for (int column = 0; column < width; column++) {
		pixels[0][column] = 2;
	}
	
	for (int column = 0; column < width; column++) {
		pixels[height-1][column] = 2;
	}
	
	// First pass in which there is a simple pass checking for 0 values connected to the border, from left to right.
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 0) {
				pixels[row][column] = 2;
			} else if (pixels[row][column] == 1) {
				break;
			}
		}
	}
	
	// Second pass in which there is a simple pass checking for 0 values connected to the border, from right to left.
	for (int row = height - 1; row > -1; row--) {
		for (int column = width - 1; column > -1; column--) {
			if (pixels[row][column] == 0) {
				pixels[row][column] = 2;
			} else if (pixels[row][column] == 1) {
				break;
			}
		}
	}
	
	// Third pass in which there is an 8-connectivity check for 0 values adjacent to the filled in 2 values (e.g. in 2 or 5).
	for (int i = 0; i <= height; i++) {
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (pixels[row][column] == 2) {
					if ((column + 1 < width) && (column - 1 > -1) && (row + 1 < height) && (row - 1 > -1)) {
						if (pixels[row][column + 1] == 0) {
							pixels[row][column + 1] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column] = 2;
						}
						if (pixels[row][column - 1] == 0) {
							pixels[row][column - 1] = 2;
						}
						if (pixels[row - 1][column] == 0) {
							pixels[row - 1][column] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column + 1] = 2;
						}
						if (pixels[row + 1][column - 1] == 0) {
							pixels[row + 1][column - 1] = 2;
						}
						if (pixels[row - 1][column + 1] == 0) {
							pixels[row - 1][column + 1] = 2;
						}
						if (pixels[row - 1][column - 1] == 0) {
							pixels[row - 1][column - 1] = 2;
						}
					} else if ((column + 1 == width) && (row + 1 != height) && (row - 1 != -1)) {
						if (pixels[row][column - 1] == 0) {
							pixels[row][column - 1] = 2;
						}
						if (pixels[row - 1][column] == 0) {
							pixels[row - 1][column] = 2;
						}
						if (pixels[row + 1][column - 1] == 0) {
							pixels[row + 1][column - 1] = 2;
						}
						if (pixels[row - 1][column - 1] == 0) {
							pixels[row - 1][column - 1] = 2;
						}
					} else if ((column - 1 == -1) && (row + 1 != height) && (row - 1 != -1)) {
						if (pixels[row][column + 1] == 0) {
							pixels[row][column + 1] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column] = 2;
						}
						if (pixels[row - 1][column] == 0) {
							pixels[row - 1][column] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column + 1] = 2;
						}
						if (pixels[row - 1][column + 1] == 0) {
							pixels[row - 1][column + 1] = 2;
						}
					} else if ((row + 1 == height) && (column + 1 != width) && (column - 1 != -1)) {
						if (pixels[row][column + 1] == 0) {
							pixels[row][column + 1] = 2;
						}
						if (pixels[row][column - 1] == 0) {
							pixels[row][column - 1] = 2;
						}
						if (pixels[row - 1][column] == 0) {
							pixels[row - 1][column] = 2;
						}
						if (pixels[row - 1][column + 1] == 0) {
							pixels[row - 1][column + 1] = 2;
						}
						if (pixels[row - 1][column - 1] == 0) {
							pixels[row - 1][column - 1] = 2;
						}
					} else if ((row - 1 == -1) && (column + 1 != width) && (column - 1 != -1)) {
						if (pixels[row][column + 1] == 0) {
							pixels[row][column + 1] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column] = 2;
						}
						if (pixels[row][column - 1] == 0) {
							pixels[row][column - 1] = 2;
						}
						if (pixels[row + 1][column + 1] == 0) {
							pixels[row + 1][column + 1] = 2;
						}
						if (pixels[row + 1][column - 1] == 0) {
							pixels[row + 1][column - 1] = 2;
						}
					}
				}
			}
		}
	}
	
	
	
	// Fourth pass which converts these 2s into 1s in order to separate the holes as areas of 0s.
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 2) {
				pixels[row][column] = 1;
			}
		}
	}
	
	// Check for last row of the hole.
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			if (pixels[row][column] == 0) {
				return row;
			}
		}
	}
	
	return 0;
}
