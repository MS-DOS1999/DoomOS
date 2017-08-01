OBJ=DoomKernel
CC=gcc -m32 -Wall -Wno-pointer-sign -Wno-unused-but-set-variable

all: $(OBJ) 

DoomKernel: DoomKernel.o DoomScreen.o lib.o DoomGDT.o DoomIDT.o DoomInterrupt.o DoomInt.o DoomPIC.o
	ld -m elf_i386 --oformat binary -Ttext 1000 $^ -o $@

DoomInt.o: DoomInt.asm
	nasm -f elf -o $@ $^
	
.o: .c 
	$(CC) -c $^

clean:
	rm -f $(OBJ) *.o
