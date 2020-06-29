// Author: Nathan Ellis
// Date: 30 April 2017
// Crack Captcha - This program interprets a binary image and prints the value of the 4 captcha digits given.

#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
	int height, width, start_row, start_column, box_height, box_width, bound_width, i = 0;
	int black_pixel_present[200] = {0}, column_bounds[4] = {0};
	
	// Check for the inclusion of a filename in the argument.
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
		return 1;
	}
	
	// Check that the file includes the height and width as a header of the pbm file.
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }
    
    // Read the pbm and its details into an array.
    int pixels[height][width];
    if (read_pbm(argv[1], height, width, pixels)) {
    	// Find empty columns succeeding a non-empty column in the captcha array. 
    	for (int column = 1; column < width; column++) {
    		for (int row = 0; row < height; row++) {
    			if (pixels[row][column] == 1) {
    				black_pixel_present[column] = 1;
    				break;
    			}
    			
    			if ((row == height - 1) && (black_pixel_present[column - 1] == 1)) {
 					column_bounds[i] = column;
 					i++;
 					break;
    			}
    		}
    	}
    	
    	// These are the column values which cut the captcha into its four digits.
    	int first_digit_bound = column_bounds[0] + 1;
    	int second_digit_bound = column_bounds[1] + 1;
    	int third_digit_bound = column_bounds[2] + 1;
    	int fourth_digit_bound = column_bounds[3] + 1;
    	
    	// Copy the bounds of the first digit.
    	int first_digit[height][first_digit_bound];
    	for (int row = 0; row < height; row++) {
    		for (int column = 0; column < first_digit_bound; column++) {
    			first_digit[row][column] = pixels[row][column];
    		}
    	}
    	distinguish_digit(height, first_digit_bound, first_digit);
    	
    	// Copy the bounds of the second digit.
    	int second_digit_bound_start = first_digit_bound;
    	int second_digit[height][second_digit_bound - first_digit_bound];
    	for (int row = 0; row < height; row++) {
    		for (int column = first_digit_bound; column < second_digit_bound; column++) {
    			second_digit[row][column - first_digit_bound] = pixels[row][column];
    		}
    	}
    	distinguish_digit(height, second_digit_bound - first_digit_bound, second_digit);
    	
    	// Copy the bounds of the third digit.
    	int third_digit_bound_start = second_digit_bound;
    	int third_digit[height][third_digit_bound - second_digit_bound];
    	for (int row = 0; row < height; row++) {
    		for (int column = second_digit_bound; column < third_digit_bound; column++) {
    			third_digit[row][column - second_digit_bound] = pixels[row][column];
    		}
    	}
    	distinguish_digit(height, third_digit_bound - second_digit_bound, third_digit);
    	
    	// Copy the bounds of the fourth digit.
    	int fourth_digit_bound_start = third_digit_bound;
    	int fourth_digit[height][fourth_digit_bound - third_digit_bound];
    	for (int row = 0; row < height; row++) {
    		for (int column = third_digit_bound; column < fourth_digit_bound; column++) {
    			fourth_digit[row][column - third_digit_bound] = pixels[row][column];
    		}
    	}
    	distinguish_digit(height, fourth_digit_bound - third_digit_bound, fourth_digit);
    	
    	printf("\n");
		
    }
	
    return 0;
}
