[org 0x7c00]

mov bp , 0x8000
mov sp , bp

;mov b1, 10 MOD 2

mov al, bl
call print 

mov bx , 30

cmp bx, 4
jle target_1

cmp bx, 40
jl target_2

mov al , 'C'
jmp end_target

target_1:
    mov al , 'A'
    jmp end_target

target_2:
    mov dx, Hello_world 
    mov al , dl

end_target:

;call my_print_function
mov bx, Hello_world
call _write

jmp $


%include "_write.asm"

Hello_world:
    db "Hello World!!", 0

numbers:
    db "0123456789", 0

times 510 - ($ - $$) db 0

dw 0xaa55