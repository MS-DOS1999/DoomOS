#include "DoomTypes.h"
#include "DoomGDT.h"
#include "DoomScreen.h"
#include "DoomIO.h"
#include "DoomIDT.h"

extern void scrollupDoom(doom32);
extern void putsDoom(doom8 *);

extern doom8 kY;
extern doom8 kattr;

void init_pic();

int main();

void _start(){
	
        kY = 1;
		
		kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" Loading IDT...\n");
		
		init_idt();
		
		kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" IDT loaded !\n");
		
		kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" PIC initialization...\n");
		
		init_pic();
		
		kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" PIC initialized !\n");
		
		
        kattr = 0x4E;
        putsDoom("DoomKernel >");
        kattr = 0x04;
        putsDoom(" Loading new GDT...\n");
		
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
	putsDoom(" New GDT loaded !\n");
	
	sti; //active interrupt
	
	kattr = 0x4E;
    putsDoom("DoomKernel >");
    kattr = 0x04;
    putsDoom(" Allowing interrupt\n");
	kattr = 0x07;
	
	while(1);
	
}