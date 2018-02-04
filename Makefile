
AQUA_ISO := $(shell ls aqua/aqua.iso)
AS := nasm

APT := $(shell command -v apt 2> /dev/null)
CC := $(shell command -v i686-elf-gcc 2> /dev/null)
CPPC := $(shell command -v i686-elf-g++ 2> /dev/null)

ifndef CC
CC := $(shell command -v cross_compiler/opt/cross/bin/i686-elf-gcc 2> /dev/null)
endif

ifndef CC
CC := gcc -m32
endif

ifndef CPPC
CPPC := $(shell command -v cross_compiler/opt/cross/bin/i686-elf-g++ 2> /dev/null)
endif

ifndef CPPC
CPPC := g++ -m32
endif

CFLAGS := -ffreestanding -g -Wfatal-errors -Wno-trigraphs -nostdlib
CPPFLAGS := $(CFLAGS)
ASFLAGS := -felf32
LDFLAGS := -Tbuild/linker.ld -nostdlib -lgcc -g
EMUFLAGS := -net none -serial stdio

ISO := bin/aqua.iso
KERNEL := bin/kernel.bin

KERNEL_SRC := $(shell find src/ -iname *.c -o -iname *.cpp -o -iname *.asm ! -iname kernel.asm)
KERNEL_OBJ := $(addsuffix .o,$(KERNEL_SRC))

#external_objects/game.o
EXTERNAL_OBJ := 

prebuild:
	@echo "Running Makefile ..."
	mkdir -p logs/

all: $(ISO)
	@echo "Building $(ISO) ..."

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
	$(CC) $(LDFLAGS) -o $@ src/asm/kernel.asm.o $^ src/de/main.o src/de/res.o $(EXTERNAL_OBJ) 2>&1 | tee logs/link.log

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.cpp.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c -o $@ $<

%.asm.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean: prebuild
	-rm *.log
	-rm bug_report.zip
	
	$(RM) $(KERNEL_OBJ)
	$(RM) $(ISO)
	$(RM) $(KERNEL)
	
	$(RM) src/de/main.o
	$(RM) src/de/res.o
	
	$(RM) src/c/pci/database/database.h
	echo > src/c/pci/database/vendor_count.h
	
	$(RM) aqua/aqua.iso
	$(RM) aqua/boot/kernel.bin

kill-vm: prebuild
	VBoxManage list runningvms | sed -r 's/.*\{(.*)\}/\1/' | xargs -L1 -I {} VBoxManage controlvm {} poweroff
	sleep 1

test: kill-vm
	-rm logs/serial.log
	VBoxManage startvm "AQUA OS" 2>&1 | tee logs/virtualbox.log

main: prebuild
	$(RM) src/c/c_kernel.c.o
	$(RM) src/de/main.o

update: prebuild
	$(RM) src/de/main.o
	$(RM) src/de/res.o

download: prebuild
ifdef APT
	sudo apt install virtualbox \
		xorriso \
		mtools \
		grub2-common:i386 \
		make \
		gcc \
		nasm \
		git
endif

vm-setup: prebuild
ifndef AQUA_ISO
	$(error aqua/aqua.iso was not found. You need to have build AQUA with `make all` to be able to automatically create a VirtualBox VM ...)
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
		--uartmode1 file logs/serial.log \
		\
		--usb on
	
	VBoxManage createhd --filename "virtualbox/AQUA Harddrive" --size 2048
	VBoxManage storagectl "AQUA OS" --add ide --name "IDE"
	
	VBoxManage storageattach "AQUA OS" --storagectl "IDE" --port 1 --device 0 --medium aqua/aqua.iso --type dvddrive
	VBoxManage storageattach "AQUA OS" --storagectl "IDE" --port 0 --device 0 --medium "virtualbox/AQUA Harddrive.vdi" --type hdd

pci-database: prebuild
	sh scripts/pci-database.sh 2>&1 | tee logs/pci-database.log

driver-database: pci-database
	sh scripts/driver-database.sh 2>&1 | tee logs/driver-database.log

commit: prebuild
	echo > src/c/pci/database/vendor_count.h
	sh scripts/commit.sh 2>&1 | tee logs/commit.log

cross-compiler: prebuild
ifdef APT
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

self: prebuild
	sh scripts/self.sh 2>&1 | tee logs/self.log

define echo_colour
	tput setaf 1
	@echo $1
	@tput sgr0
endef

bug: prebuild
	-rm bug_report.zip
	
	$(call echo_colour, "Please enter a breif description of your bug")
	sh scripts/bug_description.sh
	
	mkdir -p logs/extra_info/
	mkdir -p logs/extra_info/has/
	
	echo $$(date) > logs/extra_info/stamp.log
	
	echo $(APT) > logs/extra_info/has/apt.log
	echo $(CC) > logs/extra_info/has/c_compiler.log
	echo $(CPPC) > logs/extra_info/has/cpp_compiler.log
	echo $(AS) > logs/extra_info/has/as_compiler.log
	
	zip -r bug_report.zip logs/
	$(call echo_colour, "PLEASE SEND THE \"bug_report.zip\" FILE LOCATED IN THIS DIRECTORY ON THE #support CHANNEL ON MY DISCORD (https://discord.gg/ac3mX7u)")

auto: prebuild
	sh scripts/auto.sh

ultra-clean: clean
	-rm -rf cross_compiler/

flash: all
	$(call echo_colour, "WARNING This is a dangerous command. Only run this if you know what you are doing ...")
	sh scripts/flash.sh 2>&1 logs/flash.log

.PHONY: test clean main update download vm-setup cross-compiler pci-database commit all self bug auto ultra-clean kill-vm flash driver-database
