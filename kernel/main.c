#include "../driver/screen.h"
#include "printf/printf.h"

void main()
{
    int i = 0;
    clear_screen();
    while (1)
        printf("%d--\n", i++);
}
