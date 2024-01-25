#include "../driver/screen.h"
#include "printf/printf.h"
#include "interrupts/idt.h"

// keyboard handler
void irq2_handler(struct InterruptRegisters *r)
{
    char kbd_US[128] =
        {
            0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
            '\t', /* <-- Tab */
            'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
            0, /* <-- control key */
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
            '*',
            0,   /* Alt */
            ' ', /* Space bar */
            0,   /* Caps lock */
            0,   /* 59 - F1 key ... > */
            0, 0, 0, 0, 0, 0, 0, 0,
            0, /* < ... F10 */
            0, /* 69 - Num lock*/
            0, /* Scroll Lock */
            0, /* Home key */
            0, /* Up Arrow */
            0, /* Page Up */
            '-',
            0, /* Left Arrow */
            0,
            0, /* Right Arrow */
            '+',
            0, /* 79 - End key*/
            0, /* Down Arrow */
            0, /* Page Down */
            0, /* Insert Key */
            0, /* Delete Key */
            0, 0, 0,
            0, /* F11 Key */
            0, /* F12 Key */
            0, /* All other keys are undefined */
        };
    uint8_t scancode = port_byte_in(0x60);
    if (scancode >= 0 && scancode <= 127)
        printf("%c", kbd_US[scancode]);
}

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
    printf("%d %d\n", 52, 78);
    printf("/: ");
    initIdt();
    irq_install_handler(1, irq2_handler); // Install keyboard handler on IRQ 1
}
