#include "DoomTypes.h"
#include "DoomScreen.h"
#include "DoomKeyboard.h"
#include "DoomIO.h"

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
	}
}

void isr_kbd_int(){
	
	doom8 i;
	static doom32 lshift_enable;
	static doom32 rshift_enable;
	static doom32 alt_enable;
	static doom32 ctrl_enable;
	static doom32 keyboardCounter = 0;
	
	do{
		
		i = inb(0x64);
		
	}while((i & 0x01) == 0);
	
	i = inb(0x60);
	i--;
	
	if((i == 0x0D)){
		if(keyboardCounter > 0){
			if(kX == 0){
				kX = 79;
				kY--;
			}
			else{
				kX--;
			}
		
			putcharDoom(' ');
		
			if(kX == 0){
				kX = 79;
				kY--;
			}
			else{
				kX--;
			}
		
			keyboardCounter--;
		}
	}
	else if(i < 80){
		switch(i){
			case 0x29:
				lshift_enable = 1;
				break;
			case 0x35:
				rshift_enable = 1;
				break;
			case 0x1C:
				ctrl_enable = 1;
				break;
			case 0x37:
				alt_enable = 1;
				break;
			default:
				keyboardCounter++;
				putcharDoom(kbdmap[i * 4 + (lshift_enable || rshift_enable)]);
				break;
		}
	}
	else{
		
		i -= 0x80;
		switch(i){
			case 0x29:
				lshift_enable = 0;
				break;
			case 0x35:
				rshift_enable = 0;
				break;
			case 0x1C:
				ctrl_enable = 0;
				break;
			case 0x37:
				alt_enable = 0;
				break;
		}
	}
	
	show_cursorDoom();
}




