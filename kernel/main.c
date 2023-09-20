#include "../driver/screen.h"

char *video_memory;



void putchar(char c)
{
    *video_memory++ = c;
    *video_memory++ = 0x0f;
}

void clear()
{
    video_memory = (char *)0xb8000;
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
    set_cursor(0);
    video_memory = (char *)0xb8000;
}

void ft_putnbr(int nbr)
{
    if(nbr < 0)
    {
        nbr *= -1;
        putchar('-');
    }
    if(nbr >= 10)
        ft_putnbr(nbr / 10);
    putchar((nbr % 10) + 48);
}

void main()
{
    clear();
    int i = 0;
    char *str = "Hello\nBrother\nHow\nAre\nyou\ndoing?";
    while (str[i])
    {
        print_char(str[i], -1,-1, 0);
        i++;
    }
    
    // ft_putnbr(offset);
    // print_char('R', 0,  1, WHITE_ON_BLACK);
}
