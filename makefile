kernalbin = kernel.bin
bootbin = boot_sector.bin


NAME = os-image

all:${NAME}


$(kernalbin):
	gcc -ffreestanding -c Kernel/main.c -o kernel.o
	ld --entry=0x1000 -o kernel.bin -Ttext=0x1000 kernel.o --oformat binary

${bootbin}:
	nasm -f bin boot_sector.asm -o ${bootbin}


${NAME}: clean $(kernalbin) ${bootbin}
	cat ${bootbin} $(kernalbin)  > ${NAME}
	qemu-system-x86_64 -hda ${NAME}

clean:
	rm -rf kernel.o ${bootbin} $(kernalbin) ${NAME}