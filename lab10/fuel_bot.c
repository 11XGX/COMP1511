#include <stdio.h>
#include <stdlib.h>
#include "trader_bot.h"

void get_action(struct bot *b, int *action, int *n) {
	// #define ACTION_MOVE           0
	// #define ACTION_BUY            1
	// #define ACTION_SELL           2
	// #define ACTION_DUMP           3

	struct location * current = b->location;

	// If Fuel Bot is not at a petrol station, should move to the closest petrol station.
	// If the closest petrol station cannot be reached in a single move, it should move the
	// maximum permitted distance towards the closest petrol station.
	if (current->type != LOCATION_PETROL_STATION) {
		int distance = nearest_fuel(b);
		if (distance > 0) {
			if (distance > b->maximum_move) {
				*action = ACTION_MOVE;
				*n = b->maximum_move;
			} else {
				*action = ACTION_MOVE;
				*n = distance;
			}
		} else {
			if (abs(distance) > b->maximum_move) {
				*action = ACTION_MOVE;
				*n = b->maximum_move;
			} else {
				*action = ACTION_MOVE;
				*n = distance;
			}
		}
	} else {
		// If Fuel Bot is at a Petrol station, and its fuel tank is full,
		// it should move the maximum permitted distance forward.
		if (b->fuel == b->fuel_tank_capacity) {
			*action = ACTION_MOVE;
			*n = b->maximum_move;
		} else {
			*action = ACTION_BUY;
			int fuelToBuy = b->fuel_tank_capacity - b->fuel;
			*n = fuelToBuy;
		}
	}
}
