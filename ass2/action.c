/************************************************************************
* FILENAME:
*		action.c
*
* FUNCTION(S):
*		get_action
*
* DESCRIPTION(S):
*       This function uses a series of checks and scenarios to decide the
*		best action for the bot to perform within a given commodity
*		trading world.
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

void get_action(struct bot *b, int *action, int *n) {
	// Set up simpler variables which store the bot's information. 
	int cash = b->cash;
	int fuel = b->fuel;
	struct location * currentLocation = b->location;
	struct cargo * currentCargo = b->cargo;
	int turnsLeft = b->turns_left;
	int fuelTankCapacity = b->fuel_tank_capacity;
	int maximumMove = b->maximum_move;
	int maximumCargoWeight = b->maximum_cargo_weight;
	int maximumCargoVolume = b->maximum_cargo_volume;
	
	// Find the distance to the nearest petrol station.
	int fuelDistance = find_closest_fuel(b);
	
	// Find the price for fuel of the nearest petrol station (also chosen above).
	// If there is fuel in the world, the price of that location is recorded.
	int fuelPrice = 0;
	if (fuelDistance != MAX_VALUE) {
		fuelPrice = find_fuel_price(b, fuelDistance);
	}
		
	// IF THE BOT IS NOT CARRYING CARGO...
	if (currentCargo == NULL) {
		// Search and store the names of all sellers.
		char * sellerNames[MAX_LOCATIONS];
		// (Initialisation of String Array)
		for (int i = 0; i < MAX_LOCATIONS; i++) {
			sellerNames[i] = "No Location";
		}
		
		find_seller_names(b, sellerNames);
		// Search and store the names of the sellers' commodities.
		char * commodityNames[MAX_LOCATIONS];
		// (Initialisation of String Array)
		for (int i = 0; i < MAX_LOCATIONS; i++) {
			commodityNames[i] = "No Commodity";
		}
		find_seller_commodity_names(b, sellerNames, commodityNames);

		// Copy the sellers' commodities into a new collective 2D array, 'locationNames'.
		// Search and store the highest-priced buyers of the sellers' commodities, with
		// repetition of a buyer's name allowed.
		char * locationNames[MAX_LOCATIONS][2];
		// (Initialisation of String Array)
		for (int i = 0; i < MAX_LOCATIONS; i++) {
			locationNames[i][SELLER_NAME] = "No Location";
			locationNames[i][BUYER_NAME] = "No Location";
		}
		find_relevant_buyer_names(b, sellerNames, commodityNames, locationNames);

		// Search and store the prices and quantities offered by the found sellers and buyers.
		// Search and store the weight and volume of each commodity with a seller/buyer relationship.
		int prices[MAX_LOCATIONS][2] = {{0}};
		int quantities[MAX_LOCATIONS][2] = {{0}};
		int cargoWeights[MAX_LOCATIONS] = {0};
		int cargoVolumes[MAX_LOCATIONS] = {0};
		find_location_information(b, locationNames, prices, quantities, cargoWeights, cargoVolumes);

		// Search and store each seller's distance from the current location.
		// Search and store each buyer's distance from the current location.
		// Search and store each total trip's distance from the current location.
		int sellerDistances[MAX_LOCATIONS];
		int buyerDistances[MAX_LOCATIONS];
		int tripDistances[MAX_LOCATIONS];
		// (Initialisation of Arrays)
		for (int i = 0; i < MAX_LOCATIONS; i++) {
			sellerDistances[i] = MAX_VALUE;
			buyerDistances[i] = MAX_VALUE;
			tripDistances[i] = MAX_VALUE;
		}
		find_distance_information(b, locationNames, sellerDistances, buyerDistances, tripDistances);

		// Using tripDistances, calculate how much it will cost to conduct each possible trip.
		int fullTripCosts[MAX_LOCATIONS] = {0};
		find_full_trip_costs(b, fuelPrice, tripDistances, fullTripCosts);

		// For each seller/buyer relationship, use the collected information to determine the best
		// commodities to be bought and sold.
		char * orderedLocationNames[MAX_LOCATIONS][2];
		// (Initialisation of String Array)
		for (int i = 0; i < MAX_LOCATIONS; i++) {
			orderedLocationNames[i][SELLER_NAME] = "No Location";
			orderedLocationNames[i][BUYER_NAME] = "No Location";
		}
		order_location_names(b, locationNames, prices, quantities, cargoWeights, cargoVolumes, sellerDistances, buyerDistances, tripDistances, fullTripCosts, orderedLocationNames);
		
		// If there are no more buyer/seller relationships with profit.
		if (strcmp(orderedLocationNames[0][0], "No Location") == 0) {
			// Bot does not move.
			*action = ACTION_MOVE;
			*n = 0;
		}
		// If there are not enough turns left to move to the seller AND buy AND move from the
		// seller to the buyer AND sell (minimum 4 moves).
		else if (turnsLeft < 2 + ceil(abs(sellerDistances[0])/(double)(maximumMove)) + ceil(abs(sellerDistances[0] - buyerDistances[0])/(double)(maximumMove))) {
			// Bot does not move.
			*action = ACTION_MOVE;
			*n = 0;
		}
		// If there is not enough fuel to move to the seller AND move from the seller to the buyer.
		else if (fuelDistance == MAX_VALUE && fuel < abs(sellerDistances[0]) + abs(sellerDistances[0] - buyerDistances[0])) {
			// Bot does not move.
			*action = ACTION_MOVE;
			*n = 0;
		}
		// If none of the prior checks are met, then the bot proceeds to move to the best seller found.
		else {
			// Find the distance to the best seller found.
			int sellerDistance = sellerDistances[0];

			// Find the distance to the best buyer found.
			int buyerDistance = buyerDistances[0];

			// Find the expected buying quantity of the chosen buyer/seller relationship.
			int expectedBuyingQuantity = find_expected_buying_quantity(b, sellerDistance, cargoWeights, cargoVolumes, prices, quantities);

			// If there are more than 5 turns left AND there is fuel in the world AND the bot is not
			// carrying enough fuel to make the seller distance.
			if (turnsLeft > 5 && fuelDistance != MAX_VALUE && fuel < abs(sellerDistances[0]) + abs(sellerDistances[0] - fuelDistance)) {
				// If not at a petrol station, move to the nearest petrol station.
				if (fuelDistance != 0) {
					*action = ACTION_MOVE;
					*n = fuelDistance;
				}
				// If at a petrol station, buy fuel to fill the fuel tank.
				else {
					*action = ACTION_BUY;
					*n = fuelTankCapacity - fuel;
				}
			}
			// If the bot finds itself at a petrol station during movement, buy fuel to fill the fuel tank.
			else if (fuel < fuelTankCapacity && fuelDistance == 0 && cash > fuelPrice) {
				*action = ACTION_BUY;
				*n = fuelTankCapacity - fuel;
			}
			else {
				// If the bot is not carrying cargo and not at a seller.
				if (sellerDistance != 0) {
					// If the bot is not carrying cargo, not at a seller and not at a buyer.
					// Move to the seller.
					*action = ACTION_MOVE;
					*n = sellerDistance;
				}
				// If the bot is not carrying cargo and is CURRENTLY AT a seller.
				else {
					// Buy the maximum amount of cargo.
					*action = ACTION_BUY;
					*n = expectedBuyingQuantity;
				}
			}
		}
	}

	// IF THE BOT IS CARRYING CARGO...
	else {
		// Find the best buyer of the cargo which the bot currently holds.
		int buyerDistance = find_buyer_from_cargo(b);
		
		/*
		// (FAILED) MULTIPLAYER CONDITION: If bot has cargo, but there is no longer a buyer (should only
		// happen when another bot has reduced the quantity of a buyer between turns).
		int numberOfBots = 0;
			
		struct bot_list * botCurrent = currentLocation->bots;
		
		while (botCurrent != NULL) {
			numberOfBots++;
			botCurrent = botCurrent->next;
		}
		
		struct location * multiplayerBuyer = currentLocation;
		
		if (buyerDistance >= 0) {
			for (int i = 0; i < buyerDistance; i++) {
				multiplayerBuyer = multiplayerBuyer->next;
			}
		} else {
			for (int i = 0; i > buyerDistance; i--) {
				multiplayerBuyer = multiplayerBuyer->previous;
			}
		}
		
		if (multiplayerBuyer->quantity < numberOfBots) {
			// Find the closest dump.
			int dumpDistance = find_closest_dump(b);
			if (dumpDistance != 0) {
				*action = ACTION_MOVE;
				*n = dumpDistance;
			} else {
				*action = ACTION_DUMP;
			}
		}*/
		
		// If there are more than 5 turns left AND there is fuel in the world AND the bot is not
		// carrying enough fuel to make the seller distance.
		if (turnsLeft > 5 && fuelDistance != MAX_VALUE && fuel < abs(buyerDistance) + abs(buyerDistance - fuelDistance)) {
			if (fuelDistance != 0) {
				*action = ACTION_MOVE;
				*n = fuelDistance;
			} else {
				*action = ACTION_BUY;
				*n = fuelTankCapacity - fuel;
			}
		} else if (fuel < fuelTankCapacity && fuelDistance == 0) {
			*action = ACTION_BUY;
			*n = fuelTankCapacity - fuel;
		}
		else {
			// If the bot is carrying cargo, not at a seller and not at a buyer.
			if (buyerDistance != 0) {
				// Move towards the buyer.
				*action = ACTION_MOVE;
				*n = buyerDistance;
			}
			// If the bot is carrying cargo, not at a seller and is CURRENTLY AT a buyer.
			else {
				// Sell the maximum amount of cargo the current quantity in the bot.
				*action = ACTION_SELL;
				*n = currentCargo->quantity;
			}
		}
	}
}
