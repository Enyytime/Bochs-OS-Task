BIN_DIR = bin



SRC_DIR = src



INC_DIR = include







all: build

prepare:

	mkdir -p $(BIN_DIR)

	dd if=/dev/zero of=$(BIN_DIR)/floppy.img bs=512 count=2880

bootloader: prepare

	nasm -f bin $(SRC_DIR)/bootloader.asm -o $(BIN_DIR)/bootloader.bin





stdlib:

	bcc -ansi -c -o $(BIN_DIR)/std_lib.o $(SRC_DIR)/std_lib.c



kernel:

	bcc -ansi -c -o $(BIN_DIR)/kernel.o $(SRC_DIR)/kernel.c

	nasm -f as86 $(SRC_DIR)/kernel.asm -o $(BIN_DIR)/kernel_asm.o



link:

	ld86 -o $(BIN_DIR)/kernel.bin -d $(BIN_DIR)/kernel.o $(BIN_DIR)/kernel_asm.o $(BIN_DIR)/std_lib.o

	# Copy bootloader to the first sector

	dd if=$(BIN_DIR)/bootloader.bin of=$(BIN_DIR)/floppy.img bs=512 count=1 conv=notrunc

	# Copy kernel to the second sector onwards

	dd if=$(BIN_DIR)/kernel.bin of=$(BIN_DIR)/floppy.img bs=512 seek=1 conv=notrunc



build: bootloader stdlib kernel link



run:

	bochs -f bochsrc.txt

clean:

	rm -rf $(BIN_DIR)