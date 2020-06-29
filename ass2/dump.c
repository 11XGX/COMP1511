/************************************************************************
* FILENAME:
*		dump.c
*
* FUNCTION(S):
*		find_closest_dump
*
* DESCRIPTION(S):
*		This function will locate the closest dump to the bot's current
*		location.
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
#include <assert.h>
#include "trader_bot.h"
#include "bot.h"

int find_closest_dump(struct bot *b) {
	int forwards = 0, backwards = 0;
	
	struct location * original = b->location;
	struct location * curr1 = b->location;
	struct location * curr2 = b->location;
	
	// Search the world for the closest dump and return the distance.
	while (1) {
		if (curr1->type == LOCATION_DUMP) {
			return forwards;
		}
		
		if (curr2->type == LOCATION_DUMP) {
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
	
	// There is never a world without a dump.
	assert(0);
}
