// Substitution - LAB06
// By Nathan Ellis & Serena Thai

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	char ch;
	char cipher[26];
	int letterValue;
	
	int i = 0;
	while (i < 26) {
        cipher[i] = argv[1][i];
		i++;
	}

	ch = getchar();
	while (ch != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			letterValue = ch - 'a';
			putchar(cipher[letterValue]);
		} else if (ch >= 'A' && ch <= 'Z') {
			letterValue = ch - 'A';
			putchar(cipher[letterValue]+('A'-'a'));
		} else {
			putchar(ch);
		}
		ch = getchar();
	}

	return 0;
}

/*
When the routine bites hard
And ambitions are low
And the resentment rides high
But emotions wont grow
And were changing our ways,
Taking different roads
Then love, love will tear us apart again
*/
