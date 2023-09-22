#include "screen.h"
#include "port.h"

char *Display_at(int height, int width)
{
    return ((char *)VIDEO_ADDRESS + get_screen_offset(height, width));
}

void push_char(int offset, char c, int attr)
{
    ((char *)VIDEO_ADDRESS)[offset] = c;
    ((char *)VIDEO_ADDRESS)[offset + 1] = attr;
}

char pop_char(int offset)
{
    return ((char *)VIDEO_ADDRESS)[offset];
}

int scrool(int offset)
{
    int width = 0;
    int height = 1;

    if (offset < get_screen_offset(MAX_HEIGHT - 1, MAX_WIDTH - 1))
        return (offset);

    while (height < MAX_HEIGHT)
    {
        width = 0;
        while (width < MAX_WIDTH * 2)
        {
            *Display_at(height - 1, width) = *Display_at(height, width);
            width++;
        }
        height++;
    }

    width = 0;
    while (width < MAX_WIDTH * 2)
    {
        *Display_at(MAX_HEIGHT - 1, width) = ' ';
        width++;
    }

    return (get_screen_offset(MAX_HEIGHT - 1, 0));
}

void clear_screen()
{
    int height = 0;
    int width = 0;
    while (height < MAX_WIDTH)
    {
        width = 0;

        while (width < MAX_HEIGHT)
        {
            push_char((height * MAX_HEIGHT + width) * 2, ' ', WHITE_ON_BLACK);
            width++;
        }
        height++;
    }
    set_cursor(0);
}

void print_char(char c, int height, int width, char attr)
{
    int offset;
    if (!attr)
        attr = WHITE_ON_BLACK;
    if (height >= 0 && width >= 0 && width < MAX_WIDTH && height < MAX_HEIGHT)
        offset = get_screen_offset(height, width);
    else
        offset = get_cursor();
    if (c == '\n')
        offset = get_screen_offset(offset / (2 * MAX_WIDTH), LAST_WIDTH_INDEX);
    else
        push_char(offset, c, attr);
    offset = scrool(offset += 2);
    set_cursor(offset);
}

int get_screen_offset(int height, int width)
{
    return ((height * MAX_WIDTH + width) * 2);
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
