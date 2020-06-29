#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 50000

int main (int argc, char *argv[]) {
	int i, largest, largest2;	
	int letterValue = 0;
	int counts[26] = {0};
	int counts2[26] = {0};
	char ch;
	char decryptedText[MAX_LENGTH] = {0};

	FILE *stream;
	stream = fopen(argv[1], "r");
	fread(decryptedText, 1, MAX_LENGTH, stream);
	fclose(stream);

	ch = getchar();
	while (ch != EOF) {	
		if (ch >= 'a' && ch <= 'z') {
			letterValue = ch - 'a';
			counts[letterValue] = counts[letterValue] + 1;
		} else if (ch >= 'A' && ch <= 'Z') {
			letterValue = ch - 'A';
			counts[letterValue] = counts[letterValue] + 1;
		}
		ch = getchar();
	}

	i = 1;
	largest = 0;
	while (i < 26) {
		if (counts[i-1] < counts[i]) {
			largest = i;
		}
		i++;
	}

	int j = 0;
	while (decryptedText[j] != 0) {
		if (decryptedText[j] >= 'a' && decryptedText[j] <= 'z') {
			letterValue = ch - 'a';
			counts2[letterValue] = counts2[letterValue] + 1;
		} else if (decryptedText[j] >= 'A' && decryptedText[j] <= 'Z') {
			letterValue = ch - 'A';
			counts2[letterValue] = counts2[letterValue] + 1;
		}	
		j++;
	}

	i = 1;
	largest2 = 0;
	while (i < 26) {
		if (counts2[i-1] < counts2[i]) {
			largest2 = i;
		}
		i++;
	}

	int shift;	
	if (largest2 >= largest) {
		shift = largest2 - largest;
	} else {
		shift = largest - largest2;
	}

	printf("%d", shift);

	return 0;
}
