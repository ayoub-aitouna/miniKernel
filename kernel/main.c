#include "../driver/screen.h"

void main()
{
    clear_screen();

    int i = 0;
    int max = 0;
    int j;
    while (i <= 100)
    {
        ft_putnbr(i);
        j = 0;
        max = (max >= 64 ? 0 : max + 1);
        while (j < max)
        {
            put_str("-");
            j++;
        }

        put_str("\n");
        i++;
    }

    // put_str("hellohey");
}
