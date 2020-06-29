#include <stdio.h>
#include "farnarkle.h"

int main (void) {
	int hidden_sequence[N_TILES];
	int guess[N_TILES];
	int turn = 1;
	
	create_random_tiles(hidden_sequence);

	printf("Enter guess for turn %d: ", turn);

	if (read_tiles(guess) != 1) {
			printf("Could not read guess\n");
			return 1;
	}
	printf("%d farnarkles ", count_farnarkles(hidden_sequence, guess));
	printf("%d arkles\n", count_arkles(hidden_sequence, guess));
    turn++;
	
	while (count_farnarkles(hidden_sequence, guess) < N_TILES) {
		printf("Enter guess for turn %d: ", turn);
		
		if (read_tiles(guess) != 1) {
			printf("Could not read guess\n");
			return 1;
		}
		printf("%d farnarkles ", count_farnarkles(hidden_sequence, guess));
		printf("%d arkles\n", count_arkles(hidden_sequence, guess));
		turn++;
	}

	printf("You win\n");
	
	return 0;
}
