#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS   0xb8000
#define WHITE_ON_BLACK  0x0f
#define MAX_ROWS        80
#define MAX_COLS        25

// screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
void print_char(char c, int row, int cols, char attr);

int get_cursor();
void set_cursor(int offset);
int get_screen_offset(int row, int cols);
#endif