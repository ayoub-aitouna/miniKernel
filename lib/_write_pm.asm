[bits 32] ; using 32-bit protected mode

; define constants
VIDOE_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x01

 _write_pm:
     pusha
     mov edx, VIDOE_MEMORY
     wrt_pm_loop:

         mov al, [ebx]
         mov ah, WHITE_ON_BLACK

         cmp al, 0
         je wrt_pm_end

         mov [edx], ax

         add ebx, 1
         add edx, 2

         jmp wrt_pm_loop

 wrt_pm_end:
     popa
     ret
