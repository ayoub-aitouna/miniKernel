NAME =  bin/os-image
SRC		= $(wildcard kernel/*.c driver/*.c)
OBJ_DIR	= .compiled

KERNEL_ENTRY = kernel/kernel_entry.asm

OBJ		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

KERNEL_ENTRY_OBJ = $(patsubst %.asm, $(OBJ_DIR)/%.o, $(KERNEL_ENTRY))

cc		= gcc
CFLAGS	= -ffreestanding -m32

kernelbin = bin/kernel.bin
bootbin = bin/boot_sector.bin


all: run

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(cc) $(CFLAGS) -c $< -o $@ 

$(KERNEL_ENTRY_OBJ) : $(KERNEL_ENTRY)
	@mkdir -p $(dir $@)
	nasm $^ -f elf32 -o $(KERNEL_ENTRY_OBJ)

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
	qemu-system-x86_64 -fda ${NAME}

clean:
	rm -rf $(OBJ) $(bootbin) $(kernelbin) ${NAME}