#include "screen.h"
#include "port.h"

/**
 * [0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9]
 * [10,11,12,13,14,15,16,17,18,19]
 * a[1][2] = 10 * 1 + 2 = 12
 * */



void print_char(char c, int row, int cols, char attr)
{
    int offset;
    if(!attr)
        attr = WHITE_ON_BLACK;
    if(row >= 0 && cols >= 0)
        offset = get_screen_offset(row, cols);
    else
        offset = get_cursor();
    
    if(c == '\n')
    {
        offset += (160 - ((offset) % 160));
        set_cursor(offset);
        return;
    }
    *(char *)(VIDEO_ADDRESS + offset) = c;
    *(char *)(VIDEO_ADDRESS + offset + 1) = WHITE_ON_BLACK;

    offset += 2;
    set_cursor(offset);
}



int get_screen_offset(int row, int cols)
{
    return (2 * (MAX_ROWS * row + cols));
}

int get_cursor()
{
    // reg 14: which is the high byte of the cursor's offset 
    // reg 15: which is the low byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return (offset * 2);
}


void set_cursor(int offset)
{
    int index = offset / 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (index >> 8));
    
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (index & 0x00ff));

}