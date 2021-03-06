#include <stdio.h>
#include "trader_bot.h"

void print_world(struct bot *b) {
	int locationCounter = 1;
	int check = 1;
	int type, quantity, price;
	char *commodityName, *name, *firstPointer;
	firstPointer = b->location->name;
	
	while (check == 1) {
		// Set all information of the location into a set of variables.
		name = b->location->name;
		type = b->location->type;
		
		if (locationCounter != 1 && name == firstPointer) {
			break;
		}
		
		printf("%s: ", name);
		
		if (type == LOCATION_START) {
			printf("start\n");
		} else if (type == LOCATION_SELLER) {
			quantity = b->location->quantity;
			commodityName = b->location->commodity->name;
			price = b->location->price;
			printf("will sell %d units of %s for $%d\n", quantity, commodityName, price);
		} else if (type == LOCATION_BUYER) {
			quantity = b->location->quantity;
			commodityName = b->location->commodity->name;
			price = b->location->price;
			printf("will buy %d units of %s for $%d\n", quantity, commodityName, price);
		} else if (type == LOCATION_PETROL_STATION) {
			quantity = b->location->quantity;
			price = b->location->price;
			printf("Petrol station %d units of available fuel for $%d\n", quantity, price);
		} else if (type == LOCATION_DUMP) {
			printf("dump\n");
		} else if (type == LOCATION_OTHER) {
			printf("other\n");
		}
		
		b->location = b->location->next;
		
		locationCounter++;
	}
}
