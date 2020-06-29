// Author: Nathan Ellis
// Date: 30 April 2017
// Distinguish Digit - This function interprets the partitioned section of a captcha (the box of a digit) and prints the value of the digit image given.

#include <stdio.h>
#include "captcha.h"

void distinguish_digit(int height, int width, int pixels[height][width]) {	
	int start_row, start_column, box_width, box_height, holes, bottom_hole_location, top_hole_location, max_vertical_intersections, one_check, three_check1, three_check2, four_check, five_check, seven_check;
	double horizontal_balance, vertical_balance;
	
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
		printf("8");
	} else if (holes == 1) {
		// Find the locations of top and bottom of a hole for 'single-hole digits'. 
		bottom_hole_location = get_bottom_hole_location(box_height, box_width, box_pixels);
		top_hole_location = get_top_hole_location(box_height, box_width, box_pixels);
		
		if ((bottom_hole_location <= (box_height/2)) && (top_hole_location <= (box_height/2) + 3)) {
			// If the digit contains a hole which is mostly within the bottom half of the image, it must be a 6.
			printf("6");
		} else if ((bottom_hole_location <= 10) && (top_hole_location >= (box_height - 11))){
			// If the digit contains a hole which is found in almost all of the image, it must be a 0.
			printf("0");
		} else if (four_check == 1) {
			// If the digit passes four_check, it must be a 4.
			printf("4");
		} else { 
			// Else it must be a 9.
			printf("9");
		}
	} else {
		// Find the maximum amount of vertical intersections.
		if (max_vertical_intersections <= 2) {
			if ((vertical_balance > 0.519) && (horizontal_balance > 0.44) && (horizontal_balance < 0.7) && (seven_check == 1))  {
				// If the digit passes seven_check and its balances are within the bounds are within certain values, it must be a 7.
				printf("7");
			} else if (five_check == 1) {
				// If the digit passes five_check, it must be a 5.
				printf("5");
			} else {
				// Else it must be a 1.
				printf("1");
			}
		} else {
			if (five_check == 1) {
				// If the digit passes five_check, it must be a 5.
				printf("5");
			} else if ((horizontal_balance >= 0.513) && (three_check1 == 1) && (three_check2 == 1)) {
				// If the digit passes two three_checks and its horizontal balance is relatively high, it must be a 3.
				printf("3");
			} else if (one_check == 1) {
				// If the digit passes one_check, it must be a 1.
				printf("1");
			} else {
				// Else it must be a 2.
				printf("2");
			}
		}
	}
}
