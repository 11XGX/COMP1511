//lab07 exercises
//by Nathan Ellis and Serena Thai

#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]){

    int row, column, i;
    double n_black_pixels, column_sum;
    //starts from top left and moves right
    row = height - 1;
    n_black_pixels = 0;
    column_sum = 0;
    while(row >= 0){
            column = 0;
            i = 0;
            while(column < width && i < width){
                    if(pixels[row][column] == 1){
                            n_black_pixels = n_black_pixels + 1;
                            column_sum = column_sum + i;
                    }
                i = i + 1;
                column = column + 1;
            }
        row = row - 1;
    }

    double balance = (column_sum/n_black_pixels+0.5)/width;

    return balance;


}
