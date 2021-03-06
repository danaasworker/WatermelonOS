S_SOURCES=$(wildcard *.s)
S_OBJECTS=$(S_SOURCES:.s=.o)
S_COMPILER=i686-elf-as
ASM_SOURCES=$(wildcard *.asm) $(wildcard system/*.asm) $(wildcard system/drivers/*.asm) $(wildcard system/init/*.asm)
ASM_OBJECTS=$(ASM_SOURCES:.asm=.o)
ASM_COMPILER=nasm
C_SOURCES=$(wildcard *.c)
C_OBJECTS=$(C_SOURCES:.c=.o)
C_COMPILER=i686-elf-gcc
CPP_SOURCES=$(wildcard *.cpp) $(wildcard system/*.cpp) $(wildcard system/drivers/*.cpp) $(wildcard system/init/*.cpp) $(wildcard system/gui/*.cpp) $(wildcard system/drivers/audio/*.cpp) $(wildcard system/drivers/audio/intel_hda/*.cpp) $(wildcard system/drivers/audio/ac97/*.cpp) $(wildcard system/drivers/storage/*.cpp) $(wildcard system/fs/*.cpp)
CPP_OBJECTS=$(CPP_SOURCES:.cpp=.o)
CPP_COMPILER=i686-elf-g++
INCLUDEDIR=-I ./include
CFLAGS=-w -fpermissive -masm=intel -ffreestanding -fno-exceptions -fno-rtti $(INCLUDEDIR)

all: $(S_OBJECTS) $(ASM_OBJECTS) $(C_OBJECTS) $(CPP_OBJECTS)
	cd lib; make
	cd lib/app; make
	nasm -f elf32 -o system/resources.o system/resources.asm
	$(C_COMPILER) -T linker.ld -o kernel -ffreestanding -nostdlib $^ -lgcc
	cp kernel iso/boot
	grub-mkrescue -o MyOS.iso iso
	cp MyOS.iso /mnt/d/OS

run: $(S_OBJECTS) $(ASM_OBJECTS) $(C_OBJECTS) $(CPP_OBJECTS)
	#cd lib; make
	#cd lib/app; make
	#cd ../Apps; make --always-make
	nasm -f elf32 -o system/resources.o system/resources.asm
	$(C_COMPILER) -T linker.ld -o kernel -ffreestanding -nostdlib $^ -lgcc
	cp kernel iso/boot
	grub-mkrescue -o MyOS.iso iso
	VBoxManage startvm "Watermelon"
	
run_ownBootloader: $(S_OBJECTS) $(ASM_OBJECTS) $(C_OBJECTS) $(CPP_OBJECTS)
	cd loader; make
	nasm -f elf32 -o system/resources.o system/resources.asm
	genisoimage -R -b start.bin -no-emul-boot -boot-load-size 4 -boot-info-table -boot-load-seg 0x07C0 -o MyOS.iso iso
	VBoxManage startvm "Watermelon"

copy: $(S_OBJECTS) $(ASM_OBJECTS) $(C_OBJECTS) $(CPP_OBJECTS)
	#cd lib; make
	#cd lib/app; make
	nasm -f elf32 -o system/resources.o system/resources.asm
	$(C_COMPILER) -T linker.ld -o kernel -ffreestanding -nostdlib $^ -lgcc
	cp kernel iso/boot
	grub-mkrescue -o MyOS.iso iso
	cp MyOS.iso /mnt/d/OS

build_newlib:
	cd ../../Sources/build-newlib; make all; make DESTDIR="/home/dana/compiler" install; cp -ar /home/dana/compiler/usr/i686-myos/* /home/dana/compiler/usr/

clean_newlib:
	cd ../../Sources/build-newlib; rm -rf *; ../newlib/configure --prefix=/usr --target=i686-myos

%.o: %.asm
	nasm -f elf32 -o $@ $^

%.o: %.s
	$(S_COMPILER) $^ -o $@

%.o: %.c
	$(C_COMPILER) $(CFLAGS) -c $^ -o $@

%.o: %.cpp
	$(CPP_COMPILER) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf */*.o
