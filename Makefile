TARGET = almas.elf

CC = gcc
LN_S = ln -s
RANLIB = ranlib
INCLUDES = -I./include
FLAGS = -m32 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -O2 -c -MMD
LD = ld  -melf_i386  -Ttext=0x100000 --oformat elf32-i386 -o

.S.o:
	${CC} ${INCLUDES} ${FLAGS} $<
.c.o:
	${CC} ${INCLUDES} ${FLAGS} $<

BOOT_S = load.S
BOOT_C = kernel.c

BOOT_OBJ=${BOOT_S:.S=.o} ${BOOT_C:.c=.o}

${BOOT_OBJ}: ${BOOT_SRC}

almas: ${BOOT_OBJ}
	${LD} ${TARGET} ${BOOT_OBJ}

clean::
	-${RM}  -f *~ *.lo *.o *.elf *.iso *.d
	-${RM}  -r isofiles

run: clean almas
	-mkdir isofiles
	-mkdir isofiles/boot
	-mkdir isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub/
	cp almas.elf isofiles/boot/
	grub-mkrescue -o almas-os.iso isofiles/
	qemu-system-i386 -drive format=raw,file=almas-os.iso