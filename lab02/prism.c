//Isaac Ronthal & Nathan Ellis
//Making a prism
// 9/3/2017

#include <stdio.h>

int main(void) {
    int length, width, height;
    
    printf("Please enter prism length: ");
    scanf("%d", &length);
    
    printf("Please enter prism width: ");
    scanf("%d", &width);
    
    printf("Please enter prism height: ");
    scanf("%d", &height);
    
    printf("A prism with sides %d %d %d has:\n", length, width, height);
    printf("Volume\t\t= %d\n", length*height*width);
    printf("Area\t\t= %d\n", 2*((length*height)+(length*width)+(height*width)));
    printf("Edge Length\t= %d\n", 4*(length+width+height));

    return 0;
}

