
CROSS_CC := $(shell command -v i686-elf-gcc 2> /dev/null)
CC := gcc -m32
AS := nasm

ifdef CROSS_CC
CC := i686-elf-gcc
endif

CFLAGS := -ffreestanding -g
LDFLAGS := -Tbuild/linker.ld -nostdlib -lgcc -g
ASFLAGS := -felf32
EMUFLAGS := -net none -serial stdio

ISO := bin/aqua.iso
KERNEL := bin/aqua

KERNEL_SRC := $(shell find src -name *.c -o -name *.asm)
KERNEL_OBJ := $(addsuffix .o,$(KERNEL_SRC))

$(ISO): $(KERNEL)
	@mkdir -p aqua/boot/grub
	@cp $(KERNEL) aqua/boot/aqua
	@cp build/grub.cfg aqua/boot/grub/grub.cfg
	@grub-mkrescue -o $@ aqua

$(KERNEL): $(KERNEL_OBJ)
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) src/de/main src/de/res -o $@ $^

%.c.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

%.asm.o: %.asm
	@$(AS) $(ASFLAGS) -o $@ $<

clean:
	@$(RM) $(KERNEL_OBJ) $(ISO) $(KERNEL)

.PHONY: test clean
