[BITS 32]
[ORG 0x1000]

; Affichage d'un message par ecriture dans la RAM video
    mov byte [0xB8A00], 'H'
    mov byte [0xB8A01], 0x08
    mov byte [0xB8A02], 'E'
    mov byte [0xB8A03], 0x0A
    mov byte [0xB8A04], 'L'
    mov byte [0xB8A05], 0x02
    mov byte [0xB8A06], 'L'
    mov byte [0xB8A07], 0x04
    mov byte [0xB8A08], 'O'
    mov byte [0xB8A09], 0x0E

end:
    jmp end