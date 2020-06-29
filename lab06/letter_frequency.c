// Letter Frequency - LAB06
// By Nathan Ellis & Serena Thai

#include <stdio.h>

#define N_CHAR 26

int main (void) {
	int counts[N_CHAR] = {0}, i = 0, total = 0;
	char ch = getchar();
	while (ch != EOF) {
		int letterValue = 0;
		if (ch >= 'a' && ch <= 'z') {
			total++;
			letterValue = ch - 'a';
			counts[letterValue] = counts[letterValue] + 1;
		} else if (ch >= 'A' && ch <= 'Z') {
			total++;
			letterValue = ch - 'A';
			counts[letterValue] = counts[letterValue] + 1;
		}
		ch = getchar();
	}

	double percent;
	while (i < N_CHAR) {
		percent = (counts[i]+0.0)/total;
		printf("'%c' %.6lf %d\n", i + 'a', percent, counts[i]);
		i++;
	}
	
	
	return 0;
}
