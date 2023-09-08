_write:
    push 0
    wrt_start:
        pop si
        mov dx, [bx + si]
        cmp dl, 0
        je wrt_end
        mov al, dl
        call print
        add si, 1
        push si
        jmp wrt_start
    wrt_end:
ret


print:
    pusha
    mov ah, 0x0e
    int 0x10
    popa
    ret