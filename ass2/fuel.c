/************************************************************************
* FILENAME:
*		fuel.c
*
* FUNCTION(S):
*		find_closest_fuel
*		find_fuel_price
*
* DESCRIPTION(S):
*		The first function will locate the closest petrol station to the
*		bot's current location.
*
* AUTHOR:
*		Nathan Ellis
*
* OTHER AUTHOR INFORMATION:
*		zID - z5160405
*		email - z5160405@students.unsw.edu.au
*
* COMPLETION DATE:
*		04 June 2017
*
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "trader_bot.h"
#include "bot.h"

int find_closest_fuel(struct bot *b) {
	int forwards = 0, backwards = 0;
	
	struct location * original = b->location;
	struct location * curr1 = b->location;
	struct location * curr2 = b->location;
	
	// Search the world for the closest petrol station and return the distance.
	while (1) {
		if (curr1->type == LOCATION_PETROL_STATION && curr1->quantity > 0) {
			return forwards;
		}
		
		if (curr2->type == LOCATION_PETROL_STATION && curr2->quantity > 0) {
			return backwards;
		}
		
		if (curr1 != original && (curr1 == curr2 || curr2 == curr1->next)) {
			break;
		}
		
		forwards++;
		backwards--;
		curr1 = curr1->next;
		curr2 = curr2->previous;
	}
	
	// Return MAX_VALUE if there is no fuel found in the world.
	return MAX_VALUE;
}

int find_fuel_price(struct bot *b, int fuelDistance) {
	int fuelPrice = 0;
	
	struct location * current = b->location;
	
	// Using the given fuel distance, make 'current' the location of the petrol
	// station. The fuel price will be the price of the location found.
	if (fuelDistance >= 0) {
		for (int i = 0; i < fuelDistance; i++) {
			current = current->next;
		}
		fuelPrice = current->price;
	} else {
		for (int i = 0; i > fuelDistance; i--) {
			current = current->previous;
		}
		fuelPrice = current->price;
	}
	
	return fuelPrice;
}
