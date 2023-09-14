
; passed args
; >> dh conatains how many sector  requested to read
; >> ah contains the number of sector to start reading from
; >> dl what drive to read from 
load_disk:
    push dx

    mov ah, 0x02  ; BIOS Read sector Function
    mov al, dh    ; read dh sector
    mov ch, 0x00  ; select cylinder 0
    mov dh, 0x00  ; select head 0
    mov cl, 0x02  ; start reading from second sector (fist sector is where out boot is located)


    int 0x13      ; BIOS interrupt

    jc disk_error ; if carry flag cf has been raised jump to <disk_error>
    pop dx        ; restor the initial value of dh
    cmp dh, al    ; BIOS stors how many sector has rad in al
    jne disk_error_2; if the dh and al are not equal jump to <disk_error>
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call _write
    ret

disk_error_2:
    mov bx, DISK_ERROR_MSG_2
    call _write
    ret


DISK_ERROR_MSG:
    db "Error reading from disk !!!", 0

DISK_ERROR_MSG_2:
    db "Error reading from disk : 2 !!!", 0
