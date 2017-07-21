;DoomOS BootSector
;By Julien Magnin a.k.a MSDOS

[BITS 16] ;on bosse en 16bit
[ORG 0x0] ;offset à 0

;variable
message db "BootSector is Doomed", 18, 10, 0


;on init la zone du bootSecteur et on defini la zone de la Stack

	mov ax, 0x07C00 ;on met une donnée dans l'accumulateur, ici l'adresse mémoire ou doit commencer le boot sector
	mov ds, ax
	mov es, ax ;on initialise les registres qui donne le départ du boot sector, ds et es, avec la bonne adresse mémoire
	mov ax, 0x80000
	mov ss, ax ;on defini le debut de la pile
	mov ax, 0xF000
	mov sp, ax ;et on defini ça taille et donc son debut
	
	mov si, message ; si va pointer sur la chaine
	call afficher
	
end:
	jmp end
	
	
;fonction

afficher:
	push ax
	push bx
.debut:
	lodsb ;on copie la string pointé dans si dans ds, ds va pointé sur le debut de la chaine, et si va s'incrementé sur la chaine pour la parcourir
	cmp al, 0 ;ce que pointe si est renvoyé dans al, ici on compare al à 0
	jz .fin ;si al = 0 la string est fini du coup ben on saute tout le code jusqu'a .fin
	mov ah, 0x0E ;ici on precise le service de l'interrupt qui va venir
	mov bx, 0x07 ;in stock l'attribut des caractère: couleurs, tailles
	int 0x10 ;et bim ! on appelle m'interupt 0x10 qui permet d'afficher des caractères
	jmp .debut; et on reviens au debut pour voir si y a encore des caractère à afficher
.fin
	pop ax
	pop bx
	ret
	
;on charge de NOP pour atteindre 512 octets
	times 510-($-$$) db 144 ;on met 510 NOP: opcode 144
	dw 0xAA55 ;et les deux dernier octet doivent-etre cette adresse pour specifier qu'on est en MBR Master Boot Record
	

	
	
	
	
	


