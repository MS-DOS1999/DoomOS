[BITS 16]
[ORG 0x0]

	jmp start
%include "FUNC.INC"

start:

    mov ax, 0x100
    mov ds, ax
    mov es, ax


    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xf000


    mov si, msg00
    call afficher

end:
    jmp end


msg00: db 'Je suis le Kernel, Noraj !', 0