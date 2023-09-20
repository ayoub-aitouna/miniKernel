#include "screen.h"
#include "port.h"

static void push_char(int offset, char c, int attr)
{
    *(char *)(VIDEO_ADDRESS + offset) = c;
    *(char *)(VIDEO_ADDRESS + offset + 1) = attr;
}

static void print_char(char c, int row, int cols, char attr)
{
    int offset;
    if (!attr)
        attr = WHITE_ON_BLACK;
    if (row >= 0 && cols >= 0)
        offset = get_screen_offset(row, cols);
    else
        offset = get_cursor();

    if (c == '\n')
        offset = get_screen_offset(offset / (2 * MAX_ROWS), 79);
    else
        push_char(offset, c, attr);
    offset += 2;
    set_cursor(offset);
}

static int get_screen_offset(int row, int cols)
{
    return (2 * (MAX_ROWS * row + cols));
}

static int get_cursor()
{
    // reg 14: which is the high byte of the cursor's offset
    // reg 15: which is the low byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return (offset * 2);
}

static void set_cursor(int offset)
{
    int index = offset / 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (index >> 8));

    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (index & 0x00ff));
}

void put_str(char *str)
{
    int i = 0;
    while (str[i])
        print_char(str[i++], -1, -1, 0);
}

void ft_putnbr(int nbr)
{
    if (nbr < 0)
    {
        nbr *= -1;
        print_char('-', -1, -1, 0);
    }
    if (nbr >= 10)
        ft_putnbr(nbr / 10);
    print_char((nbr % 10) + 48, -1, -1, 0);
}
