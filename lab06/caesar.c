// Caesar Cipher - LAB06
// By Nathan Ellis & Serena Thai

#include <stdio.h>
#include <stdlib.h>

void charOrder(int i, char ch) {	
	int letter;	
	while (ch != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			letter = ch+i-'a';
			if (ch+i >= 'a' && ch+i <= 'z') {
				putchar(ch+i);
			} else if (letter > 25) {
				while (letter > 25) {
					letter = letter - 26;
				}
				putchar(letter + 'a');
			} else if (letter < 0) {
				while (letter < 0) {
					letter = letter + 26;
				}
				putchar(letter + 'a');
			}
		} else if (ch >= 'A' && ch <= 'Z') {
			letter = ch+i-'A';
			if (ch+i >= 'A' && ch+i <= 'Z') {
				putchar(ch+i);
			} else if (letter > 25) {
				while (letter > 25) {
					letter = letter - 26;
				}
				putchar(letter + 'A');			
			} else if (letter < 0) {
				while (letter < 0) {
					letter = letter + 26;
				}
				putchar(letter + 'A');
			}
		} else {
			putchar(ch);
		}
		ch = getchar();
	}
}

int main (int argc, char*argv[]) {
	int i;
	char ch;

	i = atoi(argv[1]);
	
	ch = getchar();

	charOrder(i, ch);
	
	return 0;
}

/*
And we'll never be royals
It don't run in our blood
That kind of lux just ain't for us
We crave a different kind of buzz
*/
