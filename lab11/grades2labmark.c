// Lab 11 - Grades 2 Labmark
// Author: Nathan Ellis
// Date: 22 May 2017

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 20

int main(int argc, char * argv[]) {
	double mark = 0;
	char c;
	
	for (int i = 0; argv[1][i] != 0; i++) {
    	if (argv[1][i] == 'A' && argv[1][i+1] == '+') {
			mark = mark + 1.2;
		} else if (argv[1][i] == 'A') {
			mark = mark + 1;
		} else if (argv[1][i] == 'B') {
			mark = mark + 0.8;
		} else if (argv[1][i] == 'C') {
			mark = mark + 0.5;
		}
	}
	
	if (mark > 10) {
		mark = 10;
	}
	
	printf("%.1f\n", mark);
	
	return 0;
}
