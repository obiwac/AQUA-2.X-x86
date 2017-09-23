
import os

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
				os.system("i686-elf-gcc %s -m32 -c -ffreestanding -c -o %s" % (files[f], obj))
				objs = objs + obj + ' '

obj = "obj/main.o"
os.system("i686-elf-gcc %s -m32 -c -ffreestanding -c -o %s" % ("../main.c", obj)) #-O1
objs = objs + obj + ' '

objs = objs + "obj/res.o "
os.system("cp ../res/build/res.o obj/res.o")

os.system("ld -m elf_i386 -T build/linker.ld -o aqua/boot/kernel.bin %s" % (objs))
os.system("strip aqua/boot/kernel.bin")
os.system("cp build/grub.cfg aqua/boot/grub/grub.cfg")
os.system("rm aqua/aqua.iso")
os.system("grub-mkrescue --output=aqua/aqua.iso aqua/")

os.system("VBoxManage startvm \"AQUA 2.x glib\"")
#os.system("qemu-system-i386 aqua/aqua.iso -serial file:serial.log")
