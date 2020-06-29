// Decode Substitution - LAB06
// By Nathan Ellis & Serena Thai

#include <stdio.h>
#include <stdlib.h>

int decode(char arg[], char ch) {
	int i = 0;
	while (i < 26) {
		if (ch == arg[i]) {
			return i;
		} else if ((ch - 'A' + 'a') == arg[i]) {
			return i;
		}
		i++;
	}
	return 0;
}

int main (int argc, char *argv[]) {
	char ch;
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

	ch = getchar();
	while (ch != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			putchar(alphabet[decode(argv[1],ch)]);
		} else if (ch >= 'A' && ch <= 'Z') {
			putchar(alphabet[decode(argv[1],ch)] - 'a' + 'A');
		} else {
			putchar(ch);
		}
		ch = getchar();
	}

	return 0;
}
