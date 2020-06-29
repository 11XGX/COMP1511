// Author: Nathan Ellis
// Date: 30 April 2017
// Bounding Box - This function uses a given height and width and bounds the given digit into a smaller, bounded box.

#include <stdio.h>
#include "captcha.h"

#define MAX_VALUE 10000

void get_bounding_box(int height, int width, int pixels[height][width], int *start_row, int *start_column, int *box_height, int *box_width) {
	int row = height - 1;
	int column = width;
	int minRow = 0, maxRow = MAX_VALUE, minColumn = MAX_VALUE, maxColumn = 0;
	
	// Scan the array for the minimum and maximum column and row values of the array which contain a 1 as these are the bounding box limits.
	while (row >= 0 && row < height) {
		column = 0;
		while (column < width) {
			if (pixels[row][column] == 1 && row < maxRow) {
				maxRow = row;
			} else if (pixels[row][column] == 1 && column < minColumn) {
				minColumn = column;
			} else if (pixels[row][column] == 1 && row > minRow) {
				minRow = row;
			} else if (pixels[row][column] == 1 && column > maxColumn) {
				maxColumn = column;
			}
			column++;
		}
		row--;
	}
	
	// Compare maximum and minimum values to find the heights and widths of the bounding box for further use.
	*start_row = maxRow;
	*start_column = minColumn - 1;
	*box_height = minRow - maxRow + 1;
	*box_width = maxColumn - minColumn + 2;
}
