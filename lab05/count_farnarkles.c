#include <stdio.h>
#include "farnarkle.h"

// return number of farnkarkles
int count_farnarkles (int sequence1[N_TILES], int sequence2[N_TILES]) {
	int i = 0;
	int farnarkles = 0;
	
	while (i < N_TILES) {
		if (sequence1[i] == sequence2[i]) {
			farnarkles++;
		}
		i++;
	}
	return farnarkles;
}
