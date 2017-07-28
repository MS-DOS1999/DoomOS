OBJ=DoomBootSector

all: $(OBJ) 

DoomBootSector: DoomBootSector.asm
	nasm -f bin -o $@ $^ ;

clean:
	rm -f $(OBJ) *.o
