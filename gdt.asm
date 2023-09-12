;GDT

gdt_start:

gdt_null: ; 8 bytes of memroy
    dd 0x0
    dd 0x0

; base=0x0, limit = 0xfffff
; 1th flags (present)1 (privilege) 00 (descriptor type) 1 > 1001b
; type flags (code) 1, (conforming) 0 (readable) 1 (accessed 0) > 1010b
; 2th flags (granturity)1 (32-bit default) 1 (64-bit seg) 0 (AVL)0 -> 1100b
; present: , indicating that the segment is present in memory
; descriptor type: 1 >  code or data segment | 0 > System Segment
; conforming: does the code within the segment can be executed by code running at lower privilege levels.
gdt_code:
    dw 0xffff       ; limit (0:15)
    dw 0x0          ; base (0:15)
    db 0x0          ; base (16:23)
    db 10011010b    ; 1th flag && type flags
    db 11001111b    ; 2th flags && limit (16-19)
    db 0x0          ; base (24-31)

; same as code only changes : 
; type flags (code) 0, (expand down) 0 (writable) 1 (accessed 0) > 1010b
gdt_data:
    dw 0xffff       ; limit (0:15)
    dw 0x0          ; base (0:15)
    db 0x0          ; base (16:23)
    db 10010010b    ; 1th flag && type flags
    db 11001111b    ; 2th flags && limit (16-19)
    db 0x0          ; base (24-31)
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start