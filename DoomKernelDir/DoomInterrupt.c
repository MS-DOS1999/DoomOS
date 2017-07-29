#include "DoomTypes.h"
#include "DoomScreen.h"

void isr_default_int(){
	putsDoom("interrupt\n");
}

void isr_clock_int(){
	static doom32 tic = 0;
	static doom32 sec = 0;
	tic++;
	if(tic % 100 == 0){
		sec++;
		tic = 0;
		putsDoom("clock\n");
	}
}

void isr_kbd_int(){
	putsDoom("keyboard\n");
}