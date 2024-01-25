NAME =  bin/os-image
SRC		= $(shell find . -type f -name "*.c")
OBJ_DIR	= .compiled

KERNEL_ENTRY = $(shell find ./kernel -type f -name "*.asm")

OBJ		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

KERNEL_ENTRY_OBJ = $(patsubst %.asm, $(OBJ_DIR)/%.o, $(KERNEL_ENTRY))

cc		= /usr/opt/cross/bin/i686-elf-gcc
CFLAGS	= -ffreestanding -g -o2

kernelbin = bin/kernel.bin
bootbin = bin/boot_sector.bin


all: run

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(cc) $(CFLAGS) -c $< -o $@ 


$(OBJ_DIR)/%.o : %.asm
	@mkdir -p $(dir $@)
	nasm $^ -f elf32 -o $@

$(kernelbin) : $(KERNEL_ENTRY_OBJ) $(OBJ) 
	@mkdir -p $(dir $@)
	ld -m elf_i386 -Ttext=0x1000 -o kernel.elf  $^ 
	objcopy -O binary kernel.elf $(kernelbin)

$(bootbin) : boot/boot_sector.asm
	@mkdir -p $(dir $@)
	nasm -f bin $< -o $@

${NAME}: $(bootbin) $(kernelbin)
	cat $^  > ${NAME}

run: clean $(NAME)
	qemu-system-x86_64  -curses -fda   ${NAME}

clean:
	rm -rf $(OBJ) $(bootbin) $(kernelbin) ${NAME}


update:
	$(shell git add .)
	@echo "Enter the commit message"
	@read message; \
	git commit -m "$$message"
	git push