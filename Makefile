
TARGET = almas.elf

CC = gcc
FLAGS = -m32 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -O2 -MMD -c
LD = ld  -melf_i386  -Ttext=0x100000 --oformat elf32-i386 -o

.S.o:
	${CC} ${FLAGS} $<
.c.o:
	${CC} ${FLAGS} $<

LOAD_S = kernel/load.S
KERNEL_C = kernel/kernel.c

BLD=${LOAD_S:.S=.o} ${KERNEL_C:.c=.o} # ここにソースファイルを羅列
OBJ=$(notdir ${BLD})

almas: ${BLD}
	${LD} ${TARGET} ${OBJ}

clean::
	-rm -f *~ *.lo *.o *.elf *.iso *.d
	-rm -r isofiles

run: clean almas
	-mkdir isofiles
	-mkdir isofiles/boot
	-mkdir isofiles/boot/grub
	cp grub.cfg isofiles/boot/grub/
	cp almas.elf isofiles/boot/
	grub-mkrescue -o almas-os.iso isofiles/
	qemu-system-i386 -drive format=raw,file=almas-os.iso