#include "screen.h"
#include "port.h"

static void push_char(int offset, char c, int attr)
{
    ((char *)VIDEO_ADDRESS)[offset] = c;
    if (!attr)
        ((char *)VIDEO_ADDRESS)[offset + 1] = attr;
}

static char pop_char(int offset)
{
    return ((char *)VIDEO_ADDRESS)[offset];
}

static int scrool(int offset)
{
    // if (offset < get_screen_offset(MAX_ROWS, MAX_COLS))
    //     return (offset);
    for (int i = 1; i < MAX_COLS; i++)
    {
        for (int j = 0; j < MAX_ROWS; j++)
        {
            push_char(get_screen_offset(j, i - 1), pop_char(get_screen_offset(j, i)), 0);
        }
    }
    for (int j = 0; j < MAX_ROWS; j++)
    {
        push_char(get_screen_offset(j, MAX_COLS - 1), ' ', 0);
    }
    return get_screen_offset(0, MAX_COLS - 2);
}

void clear_screen()
{
    int i, j;
    for (i = 0; i < MAX_ROWS; i++)
    {
        for (j = 0; j < MAX_COLS; j++)
        {
            print_char(' ', i, j, WHITE_ON_BLACK);
        }
    }
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
    set_cursor(scrool(offset += 2));
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
