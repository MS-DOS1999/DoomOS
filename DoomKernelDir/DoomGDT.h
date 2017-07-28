#include "DoomTypes.h"

#define GDTBASE 0x0 //je stocke ma gdt custom au tout debut parce que OSEF
#define GDTSIZE 0xFF // nombre max de descripteur

//descripteur segments
struct gdtdesc{
	doom16 lim0_15;
	doom16 base0_15;
	doom8 base16_23;
	doom8 acces;
	doom8 lim16_19 : 4;
	doom8 other : 4;
	doom8 base24_31;
} __attribute__ ((packed));

//GDTR
struct gdtr{
	doom16 limite;
	doom32 base;
} __attribute__ ((packed));

void init_gdt_desc(doom32, doom32, doom8, doom8, struct gdtdesc *);
void init_gdt(void);

#ifdef __GDT__
	struct gdtdesc kgdt[GDTSIZE]; //GDT
	struct gdtr kgdtr; //GDTR
#else
	extern struct gdtdesc kgdt[];
	extern struct gdtr kgdtr;
#endif