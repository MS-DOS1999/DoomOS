;fonction

afficher:
	push ax
	push bx
.debut:
	lodsb ;on copie la string pointé dans si dans ds, ds va pointé sur le debut de la chaine, et si va s'incrementé sur la chaine pour la parcourir
	cmp al, 0 ;ce que pointe si est renvoyé dans al, ici on compare al à 0
	jz .fin ;si al = 0 la string est fini du coup ben on saute tout le code jusqu'a .fin
	mov ah, 0x0E ;ici on precise le service de l'interrupt qui va venir
	mov bx, 0x07 ;on stock l'attribut des caractère: couleurs, tailles
	int 0x10 ;et bim ! on appelle m'interupt 0x10 qui permet d'afficher des caractères
	jmp .debut; et on reviens au debut pour voir si y a encore des caractère à afficher
.fin:
	pop bx
	pop ax
	ret