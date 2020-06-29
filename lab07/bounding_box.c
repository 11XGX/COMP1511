//lab07 exercises
//by Nathan Ellis and Serena Thai

#include <stdio.h>
#include "captcha.h"

//need min and max row value that contains black pixels (this will be height)
//need min and max column value that contains black pixels

void get_bounding_box(int height, int width, int pixels[height][width],
                      int *start_row, int *start_column, int *box_height, int *box_width){

        int row, column, max_row, min_column, min_row, max_column;

        //for top bounding
        row = height - 1;
        while(row >= 0){
            column = 0;
            while(column < width){
                if(pixels[row][column] == 1){
                    min_row = row;
                }
                column = column + 1;
            }
            row = row - 1;
        }

        //for left bounding
        column = 0;
        while(column < width){
            row = height - 1;
            while(row >= 0){
                if(pixels[row][column] == 1){
                    max_column = column;
                }
                row = row - 1;
            }
            column = column + 1;
        }

        //for bottom bounding
        row = 0;
        while(row < height){
            column = 0;
            while(column < width){
                if(pixels[row][column] == 1){
                    max_row = row;
                }
                column = column + 1;
            }
            row = row + 1;
        }

        //for right bounding
        column = width - 1;
        while(column >= 0){
            row = height - 1;
            while(row >= 0){
                if(pixels[row][column] == 1){
                    min_column = column;
                }
                row = row - 1;
            }
            column = column - 1;
        }

        *start_row = min_row;
        *start_column = min_column;
        *box_height = max_row - min_row + 1;
        *box_width = max_column - min_column + 1;

}
