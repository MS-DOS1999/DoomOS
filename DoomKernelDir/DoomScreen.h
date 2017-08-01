#include "DoomTypes.h"

#ifdef __SCREEN__

#define VRAM 0xB8000
#define SIZESCREEN 0xFA0
#define SCREENLIM 0xB8FA0

doom8 kX = 0;  //position curseur en x
doom8 kY = 3; //position curseur en y
doom8 kattr = 0x0E; //attribut des caractères

#else

extern doom8 kX;
extern doom8 kY;
extern doom8 kattr;

#endif

void scrollupDoom(doom32);
void putcharDoom(doom8);
void putsDoom(doom8*);
void move_cursorDoom(doom8, doom8);
void show_cursorDoom();
