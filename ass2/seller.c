/************************************************************************
* FILENAME:
*		seller.c
*
* FUNCTION(S):
*		find_seller_names
*		find_seller_commodity_names
*
* DESCRIPTION(S):
*		The first function searches for and stores the names of all
*		sellers.
*
*		The second function searches for and stores the names of the
*		sellers' (found above) commodities.
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
#include <string.h>
#include "trader_bot.h"
#include "bot.h"

void find_seller_names(struct bot *b, char * sellerNames[MAX_LOCATIONS]) {
	int i = 0;

	struct location * original = b->location;
	struct location * current = b->location;
	
	// Search the world for sellers and store their names in an array.
	while (1) {
		if (current->type == LOCATION_SELLER && current->quantity > 0) {
			sellerNames[i] = current->name;
			i++;
		}
		
		if (current->next == original) {
			break;
		}
		
		current = current->next;
	}
}

void find_seller_commodity_names(struct bot *b, char * sellerNames[MAX_LOCATIONS], char * commodityNames[MAX_LOCATIONS]) {
	struct location * original = b->location;
	struct location * current = b->location;
	
	// For each seller name that has been found in the world.
	for (int i = 0; strcmp(sellerNames[i], "No Location") != 0; i++) {
		// Search the world for the commodity being sold by the given
		// seller and store their names in an array.
		while (1) {
			if (current->type == LOCATION_SELLER && current->quantity > 0) {
				commodityNames[i] = current->commodity->name;
				i++;
			}
			if (current->next == original) {
				break;
			}
		
			current = current->next;
		}
	}
}
