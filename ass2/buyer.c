/************************************************************************
* FILENAME:
*		buyer.c
*
* FUNCTION(S):
*		find_relevant_buyer_names
*		find_buyer_from_cargo
*
* DESCRIPTION(S):
*		The first function copies the sellers' commodities into a new,
*		collective 2D array, 'locationNames'.  It also searches and
*		stores the highest-priced buyers of the sellers' commodities.
*
*		The second function finds the highest-priced buyer of the
*		commodity which the bot currently holds.
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

void find_relevant_buyer_names(struct bot *b, char * sellerNames[MAX_LOCATIONS], char * commodityNames[MAX_LOCATIONS], char * locationNames[MAX_LOCATIONS][2]) {
	int highestBuyerPrice = 0;
	
	struct location * original = b->location;

	// Loop through the found seller names.
	for (int i = 0; strcmp(sellerNames[i], "No Location") != 0; i++) {
		highestBuyerPrice = 0;
		locationNames[i][SELLER_NAME] = sellerNames[i];
		
		struct location * current = original;
		
		// Search the world for the highest-priced buyer which matches the commodity name of the seller.
		while (1) {
			if (current->type == LOCATION_BUYER && current->quantity > 0 && strcmp(current->commodity->name, commodityNames[i]) == 0) {
				if (current->price > highestBuyerPrice) {
					highestBuyerPrice = current->price;
					locationNames[i][BUYER_NAME] = current->name;
				}
			}
			if (current->next == original) {
				break;
			}
			current = current->next;
		}
	}
}

int find_buyer_from_cargo(struct bot *b) {
	char * currentCargo = b->cargo->commodity->name;
	int highestBuyerPrice = 0, forwards = 0, backwards = 0;
	char * bestBuyerLocation = "No Location";
	
	struct location * original = b->location;
	struct location * current = original;
	
	// Search the world for the highest-priced buyer which matches the commodity which the bot currently holds.
	while (1) {
		if (current->type == LOCATION_BUYER && current->quantity > 0 && strcmp(current->commodity->name, currentCargo) == 0) {
			if (current->price > highestBuyerPrice) {
				highestBuyerPrice = current->price;
				bestBuyerLocation = current->name;
			}
		}
		if (current->next == original) {
			break;
		}
		current = current->next;
	} 
	
	struct location * curr1 = original;
	struct location * curr2 = original;
	
	// Search the world for the highest-priced buyer (found above) and return the distance to the found buyer location.
	while (1) {
		if (curr1->type == LOCATION_BUYER && strcmp(curr1->name, bestBuyerLocation) == 0) {
			return forwards;
		} else if (curr2->type == LOCATION_BUYER && strcmp(curr2->name, bestBuyerLocation) == 0) {
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
	
	// If no buyer is found and the search is unsuccessful, return MAX_VALUE;
	return MAX_VALUE;
}
