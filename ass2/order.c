/************************************************************************
* FILENAME:
*		order.c
*
* FUNCTION(S):
*		order_location_names
*
* DESCRIPTION(S):
*		This function receives the array containing all seller/buyer
*		relationships in the world and orders them through based on the
*		expected profits of each trip.
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

void order_location_names(struct bot *b, char * locationNames[MAX_LOCATIONS][2], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2], int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS], int sellerDistances[MAX_LOCATIONS], int buyerDistances[MAX_LOCATIONS], int tripDistances[MAX_LOCATIONS], int fullTripCosts[MAX_LOCATIONS], char * orderedLocationNames[MAX_LOCATIONS][2]) {
	int buyableProfits[MAX_LOCATIONS] = {0};
	int maximumByWeight = 0, maximumByVolume = 0, maximumByCash = 0, maximumBySeller = 0, maximumByBuyer = 0, maximumByRelationship = 0, movementsRequired = 0;
	
	// Calculate the buyable quantity and overall profit from the trip
	// for each commodity's buyer/seller relationship.	
	for (int i = 0; strcmp(locationNames[i][0], "No Location") != 0; i++) {
		// Search for the maximum amount buyable based on the commodity's weight
		// and the bot's maximum weight.
		for (int counter = 0; cargoWeights[i]*counter <= b->maximum_cargo_weight; counter++) {
			maximumByWeight = counter;
		}
	
		// Search for the maximum amount buyable based on the commodity's volume
		// and the bot's maximum volume.
		for (int counter = 0; cargoVolumes[i]*counter <= b->maximum_cargo_volume; counter++) {
			maximumByVolume = counter;
		}
		
		// Search for the maximum amount buyable based on the commodity's price
		// and the bot's held cash.
		for (int counter = 0; prices[i][SELLER_PRICE]*counter <= b->cash; counter++) {
			maximumByCash = counter;
		}
		
		// Find the maximum amount buyable based on the seller's available quantity
		// and the buyer's available quantity.
		maximumBySeller = quantities[i][SELLER_QUANTITY];
		maximumByBuyer = quantities[i][BUYER_QUANTITY];
		
		// The lowest of these two will be the maximum buyable quantity by
		// seller/buyer relationship.
		if (maximumBySeller <= maximumByBuyer) {
			maximumByRelationship = maximumBySeller;
		} else {
			maximumByRelationship = maximumByBuyer;
		}
		
		movementsRequired = ceil(abs(sellerDistances[i])/(double)(b->maximum_move)) + ceil(abs(sellerDistances[i] - buyerDistances[i])/(double)(b->maximum_move));
		
		// If the relationship has a seller/buyer of quantity 0, the buyable profit will also be 0.
		if (maximumByRelationship == 0) {
			buyableProfits[i] = 0;
		}
		// Compare the lowest amount buyable based on the weight, volume, cash, and
		// lowest relationship quantity, as this will become the buying quantity.
		else {
			if (maximumByWeight >= maximumByVolume) {
				if (maximumByRelationship >= maximumByVolume) {
					if (maximumByCash >= maximumByVolume) {
						buyableProfits[i] = maximumByVolume*prices[i][BUYER_PRICE] - maximumByVolume*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					} else {
						buyableProfits[i] = maximumByCash*prices[i][BUYER_PRICE] - maximumByCash*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					}
				} else {
					if (maximumByCash >= maximumByRelationship) {
						buyableProfits[i] = maximumByRelationship*prices[i][BUYER_PRICE] - maximumByRelationship*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					} else {
						buyableProfits[i] = maximumByCash*prices[i][BUYER_PRICE] - maximumByCash*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					}
				}
			} else {
				if (maximumByRelationship >= maximumByWeight) {
					if (maximumByCash >= maximumByWeight) {
						buyableProfits[i] = maximumByWeight*prices[i][BUYER_PRICE] - maximumByWeight*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					} else {
						buyableProfits[i] = maximumByCash*prices[i][BUYER_PRICE] - maximumByCash*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					}
				} else {
					if (maximumByCash >= maximumByRelationship) {
						buyableProfits[i] = maximumByRelationship*prices[i][BUYER_PRICE] - maximumByRelationship*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					} else {
						buyableProfits[i] = maximumByCash*prices[i][BUYER_PRICE] - maximumByCash*prices[i][SELLER_PRICE] - (fullTripCosts[i] * (movementsRequired - 1));
					}
				}
			}
		}
	}
	
	// Copy all of the location names found into 'orderedLocationNames[][]'.
	for (int i = 0; strcmp(locationNames[i][SELLER_NAME], "No Location") != 0; i++) {
		orderedLocationNames[i][SELLER_NAME] = locationNames[i][SELLER_NAME];
		orderedLocationNames[i][BUYER_NAME] = locationNames[i][BUYER_NAME];
	}
	
	// Set up simple variables to be used in sorting the location names
	// in 'orderedLocationNames[][]'.
	int temp = 0;
	char * tempString = "No String";
	
	// Search for relationships where there are no relevant buyers and move them to the end of the 'orderedLocationNames[][]'.
	for (int i = 0; i < MAX_LOCATIONS; i++) {
		for (int j = 0; strcmp(orderedLocationNames[j][SELLER_NAME], "No Location") != 0; j++) {
			if (strcmp(orderedLocationNames[j][BUYER_NAME], "No Location") == 0 && strcmp(orderedLocationNames[j+1][BUYER_NAME], "No Location") != 0) {
				temp = buyableProfits[j];
				buyableProfits[j] = buyableProfits[j+1];
				buyableProfits[j+1] = temp;
				
				temp = prices[j][SELLER_PRICE];
				prices[j][SELLER_PRICE] = prices[j+1][SELLER_PRICE];
				prices[j+1][SELLER_PRICE] = temp;
				
				temp = prices[j][BUYER_PRICE];
				prices[j][BUYER_PRICE] = prices[j+1][BUYER_PRICE];
				prices[j+1][BUYER_PRICE] = temp;
				
				temp = quantities[j][SELLER_QUANTITY];
				quantities[j][SELLER_QUANTITY] = quantities[j+1][SELLER_QUANTITY];
				quantities[j+1][SELLER_QUANTITY] = temp;
				
				temp = quantities[j][BUYER_QUANTITY];
				quantities[j][BUYER_QUANTITY] = quantities[j+1][BUYER_QUANTITY];
				quantities[j+1][BUYER_QUANTITY] = temp;
				
				temp = sellerDistances[j];
				sellerDistances[j] = sellerDistances[j+1];
				sellerDistances[j+1] = temp;
				
				temp = buyerDistances[j];
				buyerDistances[j] = buyerDistances[j+1];
				buyerDistances[j+1] = temp;
				
				temp = tripDistances[j];
				tripDistances[j] = tripDistances[j+1];
				tripDistances[j+1] = temp;
				
				temp = fullTripCosts[j];
				fullTripCosts[j] = fullTripCosts[j+1];
				fullTripCosts[j+1] = temp;
				
				tempString = orderedLocationNames[j][SELLER_NAME];
				orderedLocationNames[j][SELLER_NAME] = orderedLocationNames[j+1][SELLER_NAME];
				orderedLocationNames[j+1][SELLER_NAME] = tempString;
				
				tempString = orderedLocationNames[j][BUYER_NAME];
				orderedLocationNames[j][BUYER_NAME] = orderedLocationNames[j+1][BUYER_NAME];
				orderedLocationNames[j+1][BUYER_NAME] = tempString;
			}
		}
	}
	
	// Bubble sort orderedLocationNames[][] and the connected information of the seller/buyer
	// relationships (i.e. buyable profits, prices, quantities, seller/buyer distances)
	// by each trip's buyable profit.
	for (int i = 0; i < MAX_LOCATIONS; i++) {
		for (int j = 0; strcmp(orderedLocationNames[j][SELLER_NAME], "No Location") != 0; j++) {
			if (buyableProfits[j] < buyableProfits[j+1] && buyableProfits[j+1] != 0) {
				temp = buyableProfits[j];
				buyableProfits[j] = buyableProfits[j+1];
				buyableProfits[j+1] = temp;
				
				temp = prices[j][SELLER_PRICE];
				prices[j][SELLER_PRICE] = prices[j+1][SELLER_PRICE];
				prices[j+1][SELLER_PRICE] = temp;
				
				temp = prices[j][BUYER_PRICE];
				prices[j][BUYER_PRICE] = prices[j+1][BUYER_PRICE];
				prices[j+1][BUYER_PRICE] = temp;
				
				temp = quantities[j][SELLER_QUANTITY];
				quantities[j][SELLER_QUANTITY] = quantities[j+1][SELLER_QUANTITY];
				quantities[j+1][SELLER_QUANTITY] = temp;
				
				temp = quantities[j][BUYER_QUANTITY];
				quantities[j][BUYER_QUANTITY] = quantities[j+1][BUYER_QUANTITY];
				quantities[j+1][BUYER_QUANTITY] = temp;
				
				temp = sellerDistances[j];
				sellerDistances[j] = sellerDistances[j+1];
				sellerDistances[j+1] = temp;
				
				temp = buyerDistances[j];
				buyerDistances[j] = buyerDistances[j+1];
				buyerDistances[j+1] = temp;
				
				temp = tripDistances[j];
				tripDistances[j] = tripDistances[j+1];
				tripDistances[j+1] = temp;
				
				temp = fullTripCosts[j];
				fullTripCosts[j] = fullTripCosts[j+1];
				fullTripCosts[j+1] = temp;
				
				tempString = orderedLocationNames[j][SELLER_NAME];
				orderedLocationNames[j][SELLER_NAME] = orderedLocationNames[j+1][SELLER_NAME];
				orderedLocationNames[j+1][SELLER_NAME] = tempString;
				
				tempString = orderedLocationNames[j][BUYER_NAME];
				orderedLocationNames[j][BUYER_NAME] = orderedLocationNames[j+1][BUYER_NAME];
				orderedLocationNames[j+1][BUYER_NAME] = tempString;
			}
		}
	}
	
	// If any of the seller/buyer relationships have a buyable profit which is
	// negative or 0, the relationship should be removed as it is not useful
	// to be the bot in its plight to make the highest profit.
	for (int i = 0; i < MAX_LOCATIONS; i++) {
		if (buyableProfits[i] <= 0) {
			buyableProfits[i] == 0;
			prices[i][0] = 0;
			prices[i][1] = 0;
			quantities[i][0] = 0;
			quantities[i][1] = 0;
			sellerDistances[i] = MAX_VALUE;
			buyerDistances[i] = MAX_VALUE;
			tripDistances[i] = MAX_VALUE;
			fullTripCosts[i] = MAX_VALUE;
			orderedLocationNames[i][0] = "No Location";
			orderedLocationNames[i][1] = "No Location";
		}
	}
}


