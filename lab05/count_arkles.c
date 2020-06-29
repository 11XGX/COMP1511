#include <stdio.h>
#include "farnarkle.h"

// return number of arkles
int count_arkles(int sequence1[N_TILES], int sequence2[N_TILES]) {
	int i = 0;
	int arkles = 0;
	int checked1[N_TILES] = {0};
	int checked2[N_TILES] = {0,0,0,0};


	int a = 0;
	while (a < N_TILES) {
		if (sequence1[a] == sequence2[a]) {
			checked1[a] = 1;
			checked2[a] = 1;
		}
		a++;
	}

	while (i < N_TILES) {
	int j = 0;
		while (j < N_TILES) {
			if (sequence1[i] == sequence2[j] && checked1[i] == 0 && checked2[j] == 0) {
				arkles++;
				checked1[i] = 1;
				checked2[j] = 1;
				j = N_TILES;
			} else {
				j++;
			}
		}
		i++;
	}
	
	return arkles;
}
