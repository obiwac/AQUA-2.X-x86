
import os

withos = False

extern = bool(os.system("cp ../platforms/defs.h os/defs.h"))
os.system("find obj/ -name \"*.*\" -type f -delete")

objs = ""
ignore = []

for root, subdirs, files in os.walk("asm"):
	for f in xrange(len(files)):
		files[f] = root + '/' + files[f]
		split = files[f].split('.')
		
		if split[1] == "asm":
			obj = "obj/" + split[0][4: len(split[0])] + ".o"
			
			if not files[f] in ignore:
				os.system("nasm -f elf32 -o %s %s" % (obj, files[f]))
				objs = objs + obj + ' '

for root, subdirs, files in os.walk("c"):
	for f in xrange(len(files)):
		files[f] = root + '/' + files[f]
		split = files[f].split('.')
		
		if split[1] == 'c':
			obj = "obj/" + split[0][2: len(split[0])] + ".o"
			
			if not files[f] in ignore:
				os.system("i686-elf-gcc %s -c -ffreestanding -c -o %s -nostdlib -lgcc" % (files[f], obj))
				objs = objs + obj + ' '

if withos:
	obj = "obj/main.o"
	objs = objs + obj + " obj/res.o "

	if not extern:
		os.system("i686-elf-gcc %s -c -ffreestanding -c -o %s -nostdlib -lgcc" % ("../main.c", obj)) #-O1
		os.system("cp ../res/build/res.o obj/res.o")

	else:
		os.system("cp os/res.o obj/res.o")
		os.system("cp os/main.o obj/main.o")

#os.system("ld -m elf_i386 -T build/linker.ld -o aqua/boot/kernel.bin %s" % (objs))
os.system("i686-elf-gcc -T build/linker.ld -o aqua/boot/kernel.bin -ffreestanding -O2 -nostdlib %s -lgcc" % (objs))

#os.system("strip aqua/boot/kernel.bin")
os.system("cp build/grub.cfg aqua/boot/grub/grub.cfg")
os.system("rm aqua/aqua.iso")
os.system("grub-mkrescue --output=aqua/aqua.iso aqua/")

os.system("VBoxManage startvm \"AQUA 2.x glib\"")
#os.system("qemu-system-i386 aqua/aqua.iso -serial file:serial.log")
