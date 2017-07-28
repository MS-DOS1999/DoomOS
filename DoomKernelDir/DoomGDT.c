#include "DoomTypes.h"
#include "lib.h"

#define __GDT__
#include "DoomGDT.h"


//initialise un descripteur de segment
void init_gdt_desc(doom32 base, doom32 limite, doom8 acces, doom8 other, struct gdtdesc *desc){
	(*desc).lim0_15 = (limite & 0xFFFF);
	(*desc).base0_15 = (base & 0xFFFF);
	(*desc).base16_23 = (base & 0xFF0000) >> 16;
	(*desc).acces = acces;
	(*desc).lim16_19 = (limite & 0xF0000) >> 16;
	(*desc).other = (other & 0xF);
	(*desc).base24_31 = (base & 0xFF000000) >> 24;
	return;
}

//fonction d'initialisation sans le bios pour charger notre propre gdt
void init_gdt(){
	
	//on va initialiser les descripteurs et les copier dans kgdt
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]); //init
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]); //code / read	limite de 4GB
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]); //data / write	limite de 4GB
	init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]); //stack				aucune limite	
	
	kgdtr.limite = GDTSIZE * 8;
	kgdtr.base = GDTBASE;
	
	memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite); //on copy kgdt à la bonne adresse
	
	asm("lgdtl (kgdtr)"); //on charge kgdtr dans le registre gdt
	
	//update des selecteurs de donnée et update du segment de code avec un ljmp
	asm("movw $0x10, %ax \n \
		 movw %ax, %ds \n \
		 movw %ax, %es \n \
		 movw %ax, %fs \n \
		 movw %ax, %gs \n \
		 ljmp $0x08, $next \n \
		 next: \n");
}