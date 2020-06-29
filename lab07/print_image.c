//lab07 exercises
//by Nathan Ellis and Serena Thai

#include <stdio.h>
#include "captcha.h"

void print_image(int height, int width, int pixels[height][width]){
    int row, column;
    row = height - 1;
    while (row >= 0){
            column = 0;
            while (column < width){
                if (pixels[row][column] == 1){
                    printf("*");
                }if (pixels[row][column] == 0){
                    printf(".");
                }
            column = column + 1;
            }
        if (column == width){
            printf("\n");
        }
        row = row - 1;
    }
}
