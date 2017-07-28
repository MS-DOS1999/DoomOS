OBJ=DoomKernel
CC=gcc -m32 -Wall

all: $(OBJ) 

DoomKernel: DoomKernel.o DoomScreen.o lib.o DoomGDT.o 
	ld -m elf_i386 --oformat binary -Ttext 1000 $^ -o $@

.o: .c 
	$(CC) -c $^

clean:
	rm -f $(OBJ) *.o
