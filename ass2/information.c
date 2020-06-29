/************************************************************************
* FILENAME:
*		information.c
*
* FUNCTION(S):
*		find_location_information
*		find_distance_information
*		find_full_trip_costs
*
* DESCRIPTION(S):
*       The first function searches and stores the prices and quantities
*		offered by the found sellers and buyers. It also searches and
*		stores the weight and volume of each commodity with a seller/buyer
*		relationship.
*
*		The second function searches and stores each seller's distance,
*		buyer's distance and total trip's distance from the current
*		location.
*
*		The third function uses the total trip's distance to calculate
*		how much it will cost to conduct each possible trip.
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
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "bot.h"

void find_location_information(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2], int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS]) {
	
	struct location * original = b->location;
	
	// Loop through the found seller/buyer relationships.
	for (int i = 0; strcmp(locationNames[i][SELLER_NAME], "No Location") != 0; i++) {
		struct location * current = original;
		
		// Search the world for the found sellers and buyers listed in locationNames[],
		// and store the prices, quantities, weights and volumes found from the given
		// sellers and buyers.
		while (1) {
			if (current->type == LOCATION_SELLER && current->quantity > 0 && strcmp(current->name, locationNames[i][SELLER_NAME]) == 0) {
				prices[i][SELLER_PRICE] = current->price;
				quantities[i][SELLER_QUANTITY] = current->quantity;
				cargoWeights[i] = current->commodity->weight;
				cargoVolumes[i] = current->commodity->volume;
			} else if (current->type == LOCATION_BUYER && current->quantity > 0 && strcmp(current->name, locationNames[i][BUYER_NAME]) == 0) {
				prices[i][BUYER_PRICE] = current->price;
				quantities[i][BUYER_QUANTITY] = current->quantity;
			}
		
			if (current->next == original) {
				break;
			}
			
			current = current->next;
		}
	}
}

void find_distance_information(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int sellerDistances[MAX_LOCATIONS], int buyerDistances[MAX_LOCATIONS], int tripDistances[MAX_LOCATIONS]) {
	int forwards = 0, backwards = 0;
	
	struct location * original = b->location;
	struct location * curr1 = original;
	struct location * curr2 = original;
	
	// Loop through the found seller/buyer relationships.
	for (int i = 0; strcmp(locationNames[i][SELLER_NAME], "No Location") != 0; i++) {
		curr1 = original;
		curr2 = original;
		forwards = 0;
		backwards = 0;
		
		// Search the world for the found sellers and buyers listed in locationNames[],
		// and store the seller and buyer distances from the current location to the
		// given sellers and buyers.
		while (1) {
			if (curr1->type == LOCATION_SELLER && strcmp(locationNames[i][SELLER_NAME], curr1->name) == 0) {
				sellerDistances[i] = forwards;
			} else if (curr1->type == LOCATION_BUYER && strcmp(locationNames[i][BUYER_NAME], curr1->name) == 0) {
				buyerDistances[i] = forwards;
			}
		
			if (curr2->type == LOCATION_SELLER && strcmp(locationNames[i][SELLER_NAME], curr2->name) == 0) {
				sellerDistances[i] = backwards;
			} else if (curr2->type == LOCATION_BUYER && strcmp(locationNames[i][BUYER_NAME], curr2->name) == 0) {
				buyerDistances[i] = backwards;
			}
		
			if (curr1 != original && (curr1 == curr2 || curr2 == curr1->next)) {
				break;
			}
		
			forwards++;
			backwards--;
			curr1 = curr1->next;
			curr2 = curr2->previous;
		}
	}
	
	// While there is a seller/buyer relationship, trip distances will equal the
	// distance from the current location to the seller AND from the seller to
	// the buyer.
	for (int i = 0; sellerDistances[i] != MAX_VALUE && buyerDistances[i] != MAX_VALUE; i++) {
		tripDistances[i] = abs(sellerDistances[i]) + abs(buyerDistances[i] - sellerDistances[i]);
	}
}

void find_full_trip_costs(struct bot *b, int fuelPrice, int tripDistances[MAX_LOCATIONS], int fullTripCosts[MAX_LOCATIONS]) {
	// While there is a valid trip distance, use the found fuel price and trip
	// distance to calculate the cost of moving to the seller AND from the seller
	// to the buyer.
	for (int i = 0; tripDistances[i] != MAX_VALUE; i++) {
		fullTripCosts[i] = fuelPrice * tripDistances[i];
	}
}
