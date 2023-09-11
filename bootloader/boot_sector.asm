[bits 16]

[org 0x7c00]

 mov [BOOT_DRIVE], dl ; BIOS stors the boot drivr index in dl 

; setup stack base pointer
 mov bp , 0x8000
 mov sp , bp

 mov bx, 0x9000
 mov dh, 2
 mov dl, [BOOT_DRIVE]
 call load_disk



 mov dx, [0x9000]
 call _write_hex

 mov dx, [0x9000 + 512]
 call _write_hex


mov bx, MSG_REAL_MODE
call _write

call switch_to_pm

jmp $

%include "lib/_write.asm"
%include "lib/_write_hex.asm"
%include "lib/load_disk.asm"
%include "gdt.asm"
%include "lib/_write_pm.asm"
%include "lib/print_pm.asm"
%include "switch_to_pm.asm"


[bits 32]

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call _write_pm
    jmp $



; Global variables
BOOT_DRIVE: db 0
MSG_REAL_MODE db " Started in 16 - bit Real Mode " , 0
MSG_PROT_MODE db " Successfully landed in 32 - bit Protected Mode " , 0


; fill remaing space with 0
times 510 - ($ - $$) db 0

; magic number
dw 0xaa55



times 256 dw 0xaaaa
times 256 dw 0xffff

