#include "DoomTypes.h"
#include "DoomIO.h"

#define __SCREEN__
#include "DoomScreen.h"

void scrollupDoom(doom32 n){
	doom8 *video, *tmp;
	
	for(video = (doom8 *) VRAM; video < (doom8 *) SCREENLIM; video += 2){
		tmp = (doom8 *) (video + n * 160);
		
		if(tmp < (doom8 *) SCREENLIM){
			*video = *tmp;
			*(video+1) = *(tmp+1);
		}
		else{
			*video = 0;
			*(video+1) = 0x07;
		}
	}
	
	kY -= n;
	
	if(kY < 0){
		kY = 0;
	}
}

void putcharDoom(doom8 c){
	doom8 *video;
	
	if(c == 10){
		kX = 0;
		kY++;
	}
	else if(c == 9){
		kX = kX + 8 - (kX % 8);
	}
	else if(c == 13){
		kX = 0;
	}
	else{
		video = (doom8 *) (VRAM + 2 * kX + 160 * kY);
		*video = c;
		*(video + 1) = kattr;
		
		kX++;
		
		if(kX > 79){
			kX = 0;
			kY++;
		}
	}
	if(kY > 24){
		scrollupDoom(kY - 24);
	}
}

void putsDoom(doom8 *string){
	while(*string != 0){
		putcharDoom(*string);
		string++;
	}
}

void move_cursorDoom(doom8 x, doom8 y){
	
	doom16 c_pos;
	
	c_pos = y * 80 + x;
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, (doom8) c_pos);
	outb(0x3D4, 0x0E);
	outb(0x3D5, (doom8) (c_pos >> 8));
	
}

void show_cursorDoom(){
	move_cursorDoom(kX, kY);
}