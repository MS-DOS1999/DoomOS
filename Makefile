OBJ=DoomOS.img

all: $(OBJ) 

DoomOS.img: DoomBootSector DoomKernel
	cat DoomBootSector DoomKernel /dev/zero | dd of=DoomOS.img bs=512 count=2880

DoomKernel: DoomKernel.o DoomScreen.o
	ld -m elf_i386 --oformat binary -Ttext 1000 DoomKernel.o DoomScreen.o -o DoomKernel
	
DoomBootSector: DoomBootSector.asm
	nasm -f bin -o $@ $^

DoomKernel.o: DoomKernel.c
	gcc -m32 -c DoomKernel.c
	
DoomScreen.o: DoomScreen.c 
	gcc -m32 -c DoomScreen.c

clean:
	rm -f $(OBJ) *.o DoomBootSector DoomKernel
