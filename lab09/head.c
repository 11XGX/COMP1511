// Lab 09 - Head
// Authors: Nathan Ellis & Serena Thai
// Date: 7 May 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 4096

int main(int argc, char *argv[]) {
	char str[MAX_LENGTH];
	FILE * fp;

	if (strcmp(argv[1], "-n") == 0) {
		fp = fopen(argv[3], "r");
		for (int i = 1; i <= atoi(argv[2]); i++) {
			if (fgets(str, MAX_LENGTH, fp) != NULL) {
				printf("%s", str);
			}
		}
	} else {
		fp = fopen(argv[1], "r");
		for (int i = 1; i < 11; i++) {
			if (fgets(str, MAX_LENGTH, fp) != NULL) {
				printf("%s", str);
			}
		}
	}

	return 0;
}
