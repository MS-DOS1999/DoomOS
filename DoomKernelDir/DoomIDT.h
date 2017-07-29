#include "DoomTypes.h"

#define IDTBASE 0x800 //adresse physique ou l'on stock l'idt
#define IDTSIZE 0xFF //nb max de desc
#define INTGATE 0x8E00 //mode utilisé pour gerer les interrupts

//descripteur segment
struct idtdesc{
	doom16 offset0_15;
	doom16 select;
	doom16 type;
	doom16 offset16_31;
} __attribute__ ((packed));

struct idtr{
	doom16 limit;
	doom32 base;
} __attribute__ ((packed));

struct idtr kidtr; //registre idtr
struct idtdesc kidt[IDTSIZE];//table idt

void init_idt_desc(doom16, doom32, doom16, struct idtdesc*);
void init_idt();

