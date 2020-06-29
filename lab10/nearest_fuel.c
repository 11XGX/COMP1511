#include <stdio.h>
#include <stdlib.h>
#include "trader_bot.h"

int nearest_fuel(struct bot *b) {
	int distance, distanceCounter1 = 0, distanceCounter2 = 0;
	int originalLocationType = b->location->type;
	int cycleLocation1, cycleLocation2;

	struct location * curr1 = b->location;
	struct location * curr2 = b->location;
	
	if (originalLocationType == LOCATION_PETROL_STATION) {
		distance = 0;
	} else {
		cycleLocation1 = originalLocationType;
		cycleLocation2 = originalLocationType;
		while (curr1->type != LOCATION_PETROL_STATION) {
			// Cycle through next locations until a petrol station is found.
			curr1 = curr1->next;
			distanceCounter1++;
		}
		
		while (curr2->type != LOCATION_PETROL_STATION) {
			// Cycle through previous locations until a petrol station is found.
			curr2 = curr2->previous;
			distanceCounter2--;
		}
		
		//printf("distanceCounter1 = %d\n distanceCounter2 = %d\n", distanceCounter1, distanceCounter2);
		if (distanceCounter1 > abs(distanceCounter2)) {
			distance = distanceCounter2;
		} else {
			distance = distanceCounter1;
		}
	
	}
	
	return distance;
}
