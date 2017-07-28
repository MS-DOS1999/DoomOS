#include "DoomTypes.h"
#include "DoomGDT.h"

extern void scrollupDoom(doom32);
extern void putsDoom(doom8 *);

extern doom8 kY;
extern doom8 kattr;

int main();

void _start(){
	
        kY = 1;
        kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" Loading new gdt...\n");
		
		//init de la gdt et des segments
		init_gdt();
		
		//init du pointeur de la pile sur 0x20000
		asm("movw $0x18, %ax \n \
			 movw %ax,%ss \n \
			 movl $0x20000, %esp");
			 
		main();

}

int main(){
	
	kattr = 0x4E;
	putsDoom("DoomKernel >");
	kattr = 0x04;
	putsDoom(" New gdt loaded !\n");
	while(1);
	
}