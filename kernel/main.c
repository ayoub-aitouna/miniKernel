#include "../driver/screen.h"
#include "printf/printf.h"
#include "interrupts/idt.h"
void main()
{
    int i = 0;
    clear_screen();
    printf("\n");
    printf(" *****     *****   ***    *** ******** *****     *** ******** ***\n");
    printf(" *** **   ** ***   ***   ***  ***      *** **    *** ***      ***\n");
    printf(" ***  ** **  ***   ***  ***   ***      ***  **   *** ***      ***\n");
    printf(" ***   ***   ***   *** ***    ******** ***   **  *** ******** ***\n");
    printf(" ***    *    ***   ***  ***   ***      ***    ** *** ***      ***\n");
    printf(" ***         ***   ***   ***  ***      ***     ***** ***      ***\n");
    printf(" ***         ***(_)***    *** ******** ***      **** ******** ********\n");
    printf("\n  MiniKernel v0.0.1\n");
    printf("  Developed by  : Ayoub Aitouna\n");
    printf("  Build Date    : %s\n", __DATE__);
    printf("  Build Time    : %s\n", __TIME__);
    printf("  For more information, visit: github.com/ayoub-aitouna/miniKernel\n");
    printf("\n");
}
