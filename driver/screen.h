#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define WHITE_ON_BLACK 0x0f
#define MAX_ROWS 25
#define MAX_COLS 80

// screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void put_str(char *str);
void ft_putnbr(int nbr);

/**********************************/
/******* internal functions *******/
/**********************************/

int get_cursor();
void set_cursor(int offset);
static void print_char(char c, int row, int cols, char attr);
static void push_char(int offset, char c, int attr);
int get_screen_offset(int row, int cols);
void clear_screen();
#endif