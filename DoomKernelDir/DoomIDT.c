#include "DoomTypes.h"
#include "lib.h"
#include "DoomIO.h"
#include "DoomIDT.h"

void _asm_default_int();
void _asm_irq_0();
void _asm_irq_1();

//init descripteur
void init_idt_desc(doom16 select, doom32 offset, doom16 type, struct idtdesc* desc){
	(*desc).offset0_15 = (offset & 0xFFFF);
	(*desc).select = select;
	(*desc).type = type;
	(*desc).offset16_31 = (offset & 0xFFFF0000) >> 16;
	return;
}

void init_idt(){
	doom32 i;
	
	for(i = 0; i < IDTSIZE; i++){
		init_idt_desc(0x08, (doom32) _asm_default_int, INTGATE, &kidt[i]);
	}
	
	init_idt_desc(0x08, (doom32) _asm_irq_0, INTGATE, &kidt[32]);
	init_idt_desc(0x08, (doom32) _asm_irq_1, INTGATE, &kidt[33]);
	
	//init structure
	kidtr.limit = IDTSIZE * 8;
	kidtr.base = IDTBASE;
	
	//on copie l'idt à son adresse
	memcpy((doom8 *) kidtr.base, (doom8 *) kidt, kidtr.limit);
	
	asm("lidtl (kidtr)");
}

