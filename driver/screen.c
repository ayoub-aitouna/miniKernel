#include "screen.h"

/**
 * [0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9]
 * [10,11,12,13,14,15,16,17,18,19]
 * a[1][2] = 10 * 1 + 2 = 12
 * */

void print_char(char c, int row, int cols, char attr)
{
    int offset = 2 * (MAX_ROWS * row + cols);
    if(!attr)
        attr = WHITE_ON_BLACK;
    
    // if(row > MAX_ROWS || cols > MAX_ROWS)
    // {
        
    // }
    *(char *)(VIDEO_ADDRESS + offset) = c;
    *(char *)(VIDEO_ADDRESS + offset + 1) = 0x0a;

}