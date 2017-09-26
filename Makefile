CC				:= i686-elf-gcc
AS				:= nasm

CFLAGS			:= -ffreestanding -g
LDFLAGS			:= -Tconf/linker.ld -nostdlib -lgcc -g
ASFLAGS			:= -felf32
EMUFLAGS		:= -net none -serial stdio

ISO				:= bin/aqua.iso
KERNEL			:= bin/aqua

KERNEL_SRC		:= $(shell find kernel -name '*.[cs]')
KERNEL_OBJ		:= $(addsuffix .o,$(KERNEL_SRC))

$(ISO): $(KERNEL)
	@mkdir -p aqua/boot/grub
	@cp $(KERNEL) aqua/boot/aqua
	@cp conf/grub.cfg aqua/boot/grub/grub.cfg
	@grub-mkrescue -o $@ aqua

$(KERNEL): $(KERNEL_OBJ)
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) -o $@ $^

%.c.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

%.s.o: %.s
	@$(AS) $(ASFLAGS) -o $@ $<

test: $(ISO)
	@qemu-system-i386 -cdrom $(ISO) $(EMUFLAGS)

clean:
	@$(RM) $(KERNEL_OBJ) $(ISO) $(KERNEL)

.PHONY: test clean
