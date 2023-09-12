_write_hex:
    pusha
    mov cx, 0
    _write_hex_loop:
        cmp cx, 4
        je end
        mov ax, dx
        and ax, 0x000f
        add al, 0x30
        cmp al, 0x39
        ; skip adding 7 if it is a number
        jle part_2
        ; is letter
        add al, 7
        
    part_2:
        mov bx , HEX_OUT + 5
        sub bx , cx
        mov [bx], al
        add cx, 1
        ror dx, 4
        jmp _write_hex_loop

    end:
    mov bx, HEX_OUT
    call _write
    popa
    ret

HEX_OUT:
    db "0x0000", 0