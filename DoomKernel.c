#include "DoomTypes.h"

extern void scrollupDoom(doom32);
extern void putsDoom(doom8 *);

extern doom8 kY;
extern doom8 kattr;

void _start(){
	
        kY = 1;
        kattr = 0x04;
        putsDoom("Welcome to the DoomKernel\n");

        kattr = 0x4E;
        putsDoom("Prepare to die ! I have the PainSaw little shit !\n");

        while (1);
}