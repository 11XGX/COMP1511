#include <stdio.h>
#include <math.h>

int main (void) {
	int array[20][20], n, t, i, max=0, index, j;
	printf("Enter size of matrixn");
	scanf("%d",&n);
	int count = 1;
	i = 0;

	int round = ceil((double)n/2);

	for (i < round; i++;) {
		for (j = i; j <= n-i-1; j++) {
			array[i][j] = count++;
		}

		for (j = i+1; j <= n-i-1; j++){
			array[j][n-i-1] = count++;
		}

		for (j = n-i-2; j >= i; j--) {
			array[n-i-1][j] = count++;
		}

		for (j = n-i-2; j > i; j--) {
			array[j][i] = count++;
		}
	}

	for (i<n; i++;) {
		for (j=0; j<n; j++)
			printf("%d ", array[i][j]);
			printf("n");
	}
	return 0;
}
