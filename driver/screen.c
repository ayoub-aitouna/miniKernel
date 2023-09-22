#include "screen.h"
#include "port.h"

// void putchar(char c, int offset)
// {
//     char *video_memory;

//     video_memory = VIDEO_ADDRESS;
//     *(video_memory + offset) = c;
//     *(video_memory + (offset + 1)) = 0x0f;
// }
static void push_char(int offset, char c, int attr)
{
    ((char *)VIDEO_ADDRESS)[offset] = c;
    ((char *)VIDEO_ADDRESS)[offset + 1] = attr;
}

static char pop_char(int offset)
{
    return ((char *)VIDEO_ADDRESS)[offset];
}

static int scrool(int offset)
{
    int i, j;
    if (offset <= get_screen_offset(23, 0))
        return (offset);
    int row = 0;
    int cols;
    while (row < 10)
    {
        cols = 1;

        while (cols < 10)
        {
            char c = pop_char(get_screen_offset(cols, row));
            print_char(c, cols, row, WHITE_ON_BLACK);
            cols++;
        }
        row++;
    }

    for (int j = 0; j < MAX_COLS; j++)
    {
        push_char(get_screen_offset(MAX_ROWS, j), ' ', 0);
    }
    return get_screen_offset(MAX_ROWS - 2, 1);
}

void clear_screen()
{
    int row = 0;
    int cols = 0;
    while (row < 80)
    {
        cols = 0;

        while (cols < 25)
        {
            push_char((row * MAX_ROWS + cols) * 2, ' ', WHITE_ON_BLACK);
            cols++;
        }
        row++;
    }
    set_cursor(0);
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
    {
        push_char(offset, c, 0x00);
        offset = get_screen_offset(offset / (2 * MAX_COLS), 79);
    }
    else
        push_char(offset, c, attr);
    set_cursor(scrool(offset += 2));
}

int get_screen_offset(int row, int col)
{
    return ((row * MAX_COLS + col) * 2);
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
