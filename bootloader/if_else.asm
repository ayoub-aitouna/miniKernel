[org 0x7c00]

mov bx , 30

cmp bx, 4
jle target_1

cmp bx, 40
jl target_2


mov al , 'C'
jmp end_target_2

target_1:
    mov al , 'A'
    jmp end_target_2
end_target_1:

target_2:
    mov al , [char_b_value]
end_target_2:

mov ah, 0x0e
int 0x10




char_b_value:
    db "X"

jmp $

times 510 - ($ - $$) db 0

dw 0xaa55

