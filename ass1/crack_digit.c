// Author: Nathan Ellis
// Date: 30 April 2017
// Crack Digit - This program interprets a binary image and prints the value of the digit given.

#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
	int height, width, start_row, start_column, box_width, box_height, holes, bottom_hole_location, top_hole_location, max_vertical_intersections, one_check, three_check1, three_check2, four_check, five_check, seven_check;
	double horizontal_balance, vertical_balance;
	
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
    	// Find the bounding box of the array.
		get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
	
		// Copy the bounding box details into a new array (box_pixels).
		int box_pixels[box_height][box_width];
		copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);
		
		// Test various properties to distinguish the digit:
		// Find the balance of black pixels horizontally.
		horizontal_balance = get_horizontal_balance(box_height, box_width, box_pixels);
		
		// Find the balance of black pixels vertically.
		vertical_balance = get_vertical_balance(box_height, box_width, box_pixels);
		
		// Find the maximum amount of vertical intersections of a digit.
		max_vertical_intersections = get_max_vertical_intersections(box_height, box_width, box_pixels);
		
		// Find distinguishing features between a 4 and a 9 and return 0 or 1.
		four_check = get_four_check(box_height, box_width, box_pixels);
		
		// Find distinguishing features between a 7 and other 'non-hole digits' and return 0 or 1.
		seven_check = get_seven_check(box_height, box_width, box_pixels);
		
		// Find distinguishing features between a 5 and other 'non-hole digits' and return 0 or 1.
		five_check = get_five_check(box_height, box_width, box_pixels);
		
		// Find distinguishing features between a 3 and other 'non-hole digits' and return 0 or 1.
		three_check1 = get_three_check1(box_height, box_width, box_pixels);
		
		// Find further distinguishing features between a 3 and other 'non-hole digits' and return 0 or 1.
		three_check2 = get_three_check2(box_height, box_width, box_pixels);
		
		// Find distinguishing features between a 7 and other 'non-hole digits' and return 0 or 1.
		one_check = get_one_check(box_height, box_width, box_pixels);
		
		// Find the number of holes in a given digit.
		holes = get_holes(box_height, box_width, box_pixels);

		// These are the conditions to deduce the digit's value:
		// If the digit contains two holes, it must be an 8.
		if (holes == 2) {
			printf("8\n");
		} else if (holes == 1) {
			// Find the locations of top and bottom of a hole for 'single-hole digits'. 
			bottom_hole_location = get_bottom_hole_location(box_height, box_width, box_pixels);
			top_hole_location = get_top_hole_location(box_height, box_width, box_pixels);
			
			if ((bottom_hole_location <= (box_height/2)) && (top_hole_location <= (box_height/2) + 3)) {
				// If the digit contains a hole which is mostly within the bottom half of the image, it must be a 6.
				printf("6\n");
			} else if ((bottom_hole_location <= 10) && (top_hole_location >= (box_height - 11))){
				// If the digit contains a hole which is found in almost all of the image, it must be a 0.
				printf("0\n");
			} else if (four_check == 1) {
				// If the digit passes four_check, it must be a 4.
				printf("4\n");
			} else { 
				// Else it must be a 9.
				printf("9\n");
			}
		} else {
			// Find the maximum amount of vertical intersections.
			if (max_vertical_intersections <= 2) {
				if ((vertical_balance > 0.519) && (horizontal_balance > 0.44) && (horizontal_balance < 0.7) && (seven_check == 1))  {
					// If the digit passes seven_check and its balances are within the bounds are within certain values, it must be a 7.
					printf("7\n");
				} else if (five_check == 1) {
					// If the digit passes five_check, it must be a 5.
					printf("5\n");
				} else {
					// Else it must be a 1.
					printf("1\n");
				}
			} else {
				if (five_check == 1) {
					// If the digit passes five_check, it must be a 5.
					printf("5\n");
				} else if ((horizontal_balance >= 0.513) && (three_check1 == 1) && (three_check2 == 1)) {
					// If the digit passes two three_checks and its horizontal balance is relatively high, it must be a 3.
					printf("3\n");
				} else if (one_check == 1) {
					// If the digit passes one_check, it must be a 1.
					printf("1\n");
				} else {
					// Else it must be a 2.
					printf("2\n");
				}
			}
				
		}
		
    }
	
    return 0;
}
