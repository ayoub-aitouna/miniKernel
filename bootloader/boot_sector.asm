[org 0x7c00]
VAAR equ 60
mov [BOOT_DRIVE], dl ; BIOS stors the boot drivr index in dl 

; setup stack base pointer
mov bp , 0x8000
;setup stack pointer
mov sp , bp

mov bx, 0x9000
mov dh, 2
mov dl, [BOOT_DRIVE]
call load_disk



mov dx, [0x9000]
call _write_hex

mov al, ' '
call print

mov dx, [0x9000 + 512]
call _write_hex


jmp $

%include "lib/_write.asm"
%include "lib/_write_hex.asm"
%include "lib/load_disk.asm"




BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55


times 256 dw 0xdada
times 256 dw 0xface

