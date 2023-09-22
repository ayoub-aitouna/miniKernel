#include "../driver/screen.h"

void main()
{
    clear_screen();

    int i = 0;
    int j;
    while (i <= 405)
    {
        j = 0;
        while (j < i)
        {
            put_str("-");
            j++;
        }
        put_str("\n");
        i++;
    }
}
