
### TODO "log" target

APT := $(shell command -v apt);
CROSS_CC := $(shell command -v i686-elf-gcc)
AQUA_ISO := $(shell ls aqua/aqua.iso)

CC := gcc -m32
AS := nasm

ifdef CROSS_CC
CC := i686-elf-gcc
endif

CFLAGS := -ffreestanding -g -Wfatal-errors -Wno-trigraphs
ASFLAGS := -felf32
LDFLAGS := -Tbuild/linker.ld -nostdlib -lgcc -g
EMUFLAGS := -net none -serial stdio

ISO := bin/aqua.iso
KERNEL := bin/kernel.bin

KERNEL_SRC := $(shell find src/ -iname *.c -o -iname *.asm ! -iname kernel.asm)
KERNEL_OBJ := $(addsuffix .o,$(KERNEL_SRC))

prebuild:
	@echo "Running Makefile ..."
	mkdir -p logs/

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
	$(CC) $(LDFLAGS) -o $@ src/asm/kernel.asm.o $^ src/de/main.o src/de/res.o 2>&1 | tee logs/link.log

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.asm.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean: prebuild
	-rm *.log
	
	$(RM) $(KERNEL_OBJ)
	$(RM) $(ISO)
	$(RM) $(KERNEL)
	
	$(RM) src/de/main.o
	$(RM) src/de/res.o
	
	$(RM) src/c/pci/database/database.h
	$(RM) src/c/pci/database/vendor_count.h
	
	$(RM) aqua/aqua.iso
	$(RM) aqua/boot/kernel.bin

test: prebuild
	VBoxManage startvm "AQUA OS"

main: prebuild
	$(RM) src/c/c_kernel.c.o
	$(RM) src/de/main.o

update: prebuild
	$(RM) src/de/main.o
	$(RM) src/de/res.o

download: prebuild
ifdef $(APT)
	sudo apt install virtualbox \
		xorriso \
		mtools \
		grub \
		make \
		gcc \
		nasm
endif

vm-setup: prebuild
ifdef $(AQUA_ISO)
	$(error aqua/aqua.iso was not found. You need to have build AQUA with `make` to be able to automatically create a VirtualBox VM ...)
endif
	
	sh scripts/rm_vm.sh 2>&1 | tee logs/rm-vm.log
	mkdir -p virtualbox/
	
	-VBoxManage unregistervm "AQUA OS" --delete
	VBoxManage createvm --name "AQUA OS" --register
	
	VBoxManage modifyvm "AQUA OS" --memory 1024 \
		--audiocontroller hda \
		--nic1 nat \
		--nictype1 82540EM \
		--cableconnected1 on \
		\
		--uart1 0x3F8 4 \
		--uartmode1 file logs/serial.log
	
	VBoxManage createhd --filename "virtualbox/AQUA Harddrive" --size 2048
	VBoxManage storagectl "AQUA OS" --add ide --name "IDE"
	
	VBoxManage storageattach "AQUA OS" --storagectl "IDE" --port 1 --device 0 --medium aqua/aqua.iso --type dvddrive \
		--storagectl "IDE" --port 0 --device 0 --medium "virtualbox/AQUA Harddrive.vdi" --type hdd

pci-database: prebuild
	sh scripts/pci-database.sh 2>&1 | tee logs/pci-database.log

commit: prebuild
	sh scripts/commit.sh 2>&1 | tee logs/commit.log

cross-compiler: prebuild
ifdef $(APT)
	sudo apt install make \
		bison \
		flex \
		libgmp3-dev \
		libmpfr-dev \
		libmpc-dev \
		texinfo \
		nano
endif
	
	sh scripts/cross-compiler.sh 2>&1 | tee logs/cross-compiler.log

.PHONY: test clean main update download vm-setup cross-compiler pci-database commit
