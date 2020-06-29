// Lab 09 - Numbers
// Authors: Nathan Ellis & Serena Thai
// Date: 7 May 2017

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE * fp;

	fp = fopen(argv[3], "w");

	for (int i = atoi(argv[1]); i <= atoi(argv[2]); i++) {
		fprintf(fp,"%d\n", i);
	}

	return 0;
}
