;DoomOS BootSector
;By Julien Magnin a.k.a MSDOS
%define BASE	0x100 ;0x0100:0x0 = 0x01000
%define KSIZE	1


[BITS 16] ;on bosse en 16bit
[ORG 0x0] ;offset à 0

	jmp start
%include "FUNC.INC"

;main

start:
	;on init la zone du bootSecteur et on defini la zone de la Stack
	mov ax, 0x07C0 ;on met une donnée dans l'accumulateur, ici l'adresse mémoire ou doit commencer le boot sector
	mov ds, ax
	mov es, ax ;on initialise les registres qui donne le départ du boot sector, ds et es, avec la bonne adresse mémoire
	mov ax, 0x8000
	mov ss, ax ;on defini le debut de la pile
	mov sp, 0xF000 ;et on defini ça taille et donc son debut
	
	mov [bootdrv], dl ;ici on recupère le périphérique sur lequel l'ordi à booté et on le place dans la variable bootdrv
	
	mov si, message ; si va pointer sur la chaine
	call afficher
	
	;on charge le noyau
	xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0

    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es
	;ici on a copié le ou les secteurs du périphérique dont on a besoins pour le noyau grace à l'interupt 0x13 qui permet de copié plusieur secteur dans la RAM
	;ici on defini le debut du stockage du noyau à 0x01000(BASE) et on copie un seul secteur(KSIZE)
	
	;on saute à l'adresse du noyau pour le lancer
	jmp BASE:0 ; je rappelle que 0x0100:0x0 = 0x01000
	
	
	
;variable
	message: db "BootSector is Doomed", 0
	bootdrv: db 0
	
;on charge de NOP pour atteindre 512 octets
	times 510-($-$$) db 144 ;on met 510 NOP: opcode 144
	dw 0xAA55 ;et les deux dernier octet doivent-etre cette adresse pour specifier qu'on est en MBR Master Boot Record
	

	
	
	
	
	


