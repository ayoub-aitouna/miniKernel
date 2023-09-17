#include "../driver/screen.h"

char *video_memory;

void putchar(char c)
{
    *video_memory++ = c;
    *video_memory++ = 0x0f;
}

void clear()
{
    int row = 0;
    int cols = 0;
    while (row < 80)
    {
        cols = 0;
        while (cols < 25)
        {
            putchar(' ');
            cols++;
        }
        row++;
    }
    video_memory = (char *)0xb8000;
}

void main()
{
    video_memory = (char *)0xb8000;
    clear();

    char *str = "Hello World";
    // while (*str)
    // {
    //     putchar(*str++);
    // }
    print_char('X', 1, 0);
}
