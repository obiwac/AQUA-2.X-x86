
CROSS_CC := $(shell command -v i686-elf-gcc 2> /dev/null)
CC := gcc -m32
AS := nasm

ifdef CROSS_CC
CC := i686-elf-gcc
endif

CFLAGS := -ffreestanding -g
ASFLAGS := -felf32
LDFLAGS := -Tbuild/linker.ld -nostdlib -lgcc -g
EMUFLAGS := -net none -serial stdio

ISO := bin/aqua.iso
KERNEL := bin/kernel.bin

KERNEL_SRC := $(shell find src/ -iname *.c -o -iname *.asm ! -iname kernel.asm)
KERNEL_OBJ := $(addsuffix .o,$(KERNEL_SRC))

$(ISO): $(KERNEL)
	mkdir -p aqua/boot/grub
	cp $(KERNEL) aqua/boot/kernel.bin
	cp build/grub.cfg aqua/boot/grub/grub.cfg
	
	$(RM) aqua/aqua.iso
	
	grub-mkrescue -o $@ aqua
	cp $(ISO) aqua/aqua.iso
	
	$(RM) bin/kernel.bin
	$(RM) bin/aqua.iso

$(KERNEL): $(KERNEL_OBJ)
	$(AS) $(ASFLAGS) -o src/asm/kernel.asm.o src/asm/kernel.asm
	
	mkdir -p src/de/
	mkdir -p bin/
	
	if [ -d "../res/build" ]; then cp ../res/build/res32.o src/de/res.o; fi
	if [ -e "../main.c" ]; then $(CC) $(CFLAGS) -c ../main.c -o src/de/main.o; fi
	
	if [ -e "src/de/main.o" ]; then echo "main.o found. Delete it or run "make update" to redownload ..."; else \
		wget "http://download1644.mediafire.com/sgokis0eubcg/73g26da7uhi0vai/main.o" -O src/de/main.o; \
		wget "http://download819.mediafire.com/p6uft6o6b3pg/49hp2jcbv23aqbk/res.o" -O src/de/res.o; fi
	
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ src/asm/kernel.asm.o $^ src/de/main.o src/de/res.o

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.asm.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) $(KERNEL_OBJ)
	$(RM) $(ISO)
	$(RM) $(KERNEL)
	
	$(RM) src/de/main.o
	$(RM) src/de/res.o
	
	$(RM) aqua/aqua.iso
	$(RM) aqua/boot/kernel.bin

test:
	VBoxManage startvm "AQUA 2.x glib"

main:
	$(RM) src/c/c_kernel.c.o
	$(RM) src/de/main.o

update:
	$(RM) src/de/main.o
	$(RM) src/de/res.o

vm_setup:
	echo "TODO"

.PHONY: test clean main update vm_setup
