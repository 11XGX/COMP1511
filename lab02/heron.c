#include <stdio.h>
#include <math.h>


int main (void) {
    double a, b, c;
    printf("Enter side 1: ");
    scanf("%lf", &a);
    printf("Enter side 2: ");
    scanf("%lf", &b);
    printf("Enter side 3: ");
    scanf("%lf", &c);

    double s = (a+b+c)/2;
    double area = sqrt(s*(s-a)*(s-b)*(s-c));
    
    if ((a+b) < c || (b+c) < a || (a+c) < b) {
	printf("Error: triangle inequality violated.\n");
    } else {
	printf("Area = %.6lf\n", area);
    }

    return 0;
}
