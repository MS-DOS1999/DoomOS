#include "DoomTypes.h"

#define VRAM 0xB8000
#define SIZESCREEN 0xFA0
#define SCREENLIM 0xB8FA0

doom8 kX = 0;  //position curseur en x
doom8 kY = 3; //position curseur en y
doom8 kattr = 0x0E; //attribut des caractères

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