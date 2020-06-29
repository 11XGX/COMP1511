//lab07 exercises
//by Nathan Ellis and Serena Thai

#include <stdio.h>
#include "captcha.h"

//box_height from bounding_box specifies copy_height
//box_width from bounding_box specifies copy_width
//start_row and start_column specifies bottom left of rectangle

void copy_pixels(int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]){

                     int row, column;
                     row = 0;
                     while(row < copy_height){
                         column = 0;
                         while(column < copy_width){
                             copy[row][column] = pixels[start_row + row][start_column + column];
                             column = column + 1;
                         }
                         row = row + 1;
                     }

                 }
