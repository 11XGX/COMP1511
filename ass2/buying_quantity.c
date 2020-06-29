/************************************************************************
* FILENAME:
*		buying_quantity.c
*
* FUNCTION(S):
*		find_expected_buying_quantity
*
* DESCRIPTION(S):
*       This function searches for the maximum amount buyable based on:
*		weight, volume, cash, seller quantity and buyer quantity.  The
*		lowest quantity found from these factors, buyable by the bot will
*		be chosen as the amount to be bought from the seller.
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
#include "trader_bot.h"
#include "bot.h"

int find_expected_buying_quantity(struct bot *b, int sellerDistance, int cargoWeights[MAX_LOCATIONS], int cargoVolumes[MAX_LOCATIONS], int prices[MAX_LOCATIONS][2], int quantities[MAX_LOCATIONS][2]) {
	int maximumByWeight = 0, maximumByVolume = 0, maximumByCash = 0, maximumBySeller = 0, maximumByBuyer = 0, maximumByRelationship = 0, buyingQuantity = 0;

	struct location * current = b->location;
	
	// Cycle through the world by the given seller distance, and 'current'
	// will become the struct holding the location information.
	if (sellerDistance >= 0) {
		for (int i = 0; i < sellerDistance; i++) {
			current = current->next;
		}
	} else {
		for (int i = 0; i > sellerDistance; i--) {
			current = current->previous;
		}
	}
	
	// Search for the maximum amount buyable based on the commodity's weight
	// and the bot's maximum weight.
	for (int counter = 0; cargoWeights[0]*counter <= b->maximum_cargo_weight; counter++) {
		maximumByWeight = counter;
	}

	// Search for the maximum amount buyable based on the commodity's volume
	// and the bot's maximum volume.
	for (int counter = 0; cargoVolumes[0]*counter <= b->maximum_cargo_volume; counter++) {
		maximumByVolume = counter;
	}
	
	// Search for the maximum amount buyable based on the commodity's price
	// and the bot's held cash.
	for (int counter = 0; prices[0][SELLER_PRICE]*counter <= b->cash; counter++) {
		maximumByCash = counter;
	}
	
	// Find the maximum amount buyable based on the seller's available quantity
	// and the buyer's available quantity.
	maximumBySeller = quantities[0][SELLER_QUANTITY];
	maximumByBuyer = quantities[0][BUYER_QUANTITY];
	
	// The lowest of these two will be the maximum buyable quantity by
	// seller/buyer relationship.
	if (maximumBySeller <= maximumByBuyer) {
		maximumByRelationship = maximumBySeller;
	} else {
		maximumByRelationship = maximumByBuyer;
	}
	
	// Compare the lowest amount buyable based on the weight, volume, cash, and
	// lowest relationship quantity, as this will become the buying quantity.
	if (maximumByWeight >= maximumByVolume) {
		if (maximumByRelationship >= maximumByVolume) {
			if (maximumByCash >= maximumByVolume) {
				buyingQuantity = maximumByVolume;
			} else {
				buyingQuantity = maximumByCash;
			}
		} else {
			if (maximumByCash >= maximumByRelationship) {
				buyingQuantity = maximumByRelationship;
			} else {
				buyingQuantity = maximumByCash;
			}
		}
	} else {
		if (maximumByRelationship >= maximumByWeight) {
			if (maximumByCash >= maximumByWeight) {
				buyingQuantity = maximumByWeight;
			} else {
				buyingQuantity = maximumByCash;
			}
		} else {
			if (maximumByCash >= maximumByRelationship) {
				buyingQuantity = maximumByRelationship;
			} else {
				buyingQuantity = maximumByCash;
			}
		}
	}
	
	return buyingQuantity;
}
