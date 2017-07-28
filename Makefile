OBJ=DoomOS.img

all: $(OBJ) 

DoomOS.img: DoomBootSector DoomKernel
	cat DoomBootSectorDir/DoomBootSector DoomKernelDir/DoomKernel /dev/zero | dd of=DoomOS.img bs=512 count=2880

DoomBootSector: 
	make -C DoomBootSectorDir

DoomKernel: 
	make -C DoomKernelDir

clean:
	rm -f $(OBJ) *.o
	make -C DoomBootSectorDir clean
	make -C DoomKernelDir clean