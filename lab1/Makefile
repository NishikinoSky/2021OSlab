#export 关键字用于将下面定义的变量导入到环境中。如果不使用该关键字，通过make -C 进入到子目录中编译时下方定义的变量将会失效。
export
CROSS_=riscv64-unknown-elf-
CC=${CROSS_}gcc
LD=${CROSS_}ld
OBJCOPY=${CROSS_}objcopy

# ?= 的意思是如果该变量没定义过，则进行定义，否则忽略掉此条语句
DEBUG ?= true

ISA=rv64imafd
ABI=lp64

#该变量用于声明编译时使用头文件需要搜索的文件夹
INCLUDE = -I$(shell pwd)/include -I$(shell pwd)/arch/riscv/include
CF = -g -march=$(ISA) -mabi=$(ABI) -mcmodel=medany -ffunction-sections -fdata-sections -nostartfiles -nostdlib -nostdinc -fno-builtin -static -lgcc 


CFLAG = ${CF} ${INCLUDE} ${TASK_MM}

ifneq ($(DEBUG), )  
CFLAG += -DDEBUG_LOG
endif

#定义目标文件以及依赖。
all: vmlinux

#定义伪目标。伪目标没有依赖文件，工程根目录下通过 'make 伪目标' 可以执行伪目标下的脚本。
.PHONY: vmlinux run debug clean
vmlinux:
# -C dic 指进入dic文件夹后执行make
	${MAKE} -C arch/riscv all 
	${LD} -T arch/riscv/kernel/vmlinux.lds arch/riscv/kernel/*.o arch/riscv/libs/*.o -o vmlinux
	$(shell test -d arch/riscv/boot || mkdir -p arch/riscv/boot)
	${OBJCOPY} -O binary vmlinux arch/riscv/boot/Image
	nm vmlinux > System.map

run: vmlinux
	@qemu-system-riscv64 -nographic --machine virt -bios default -device loader,file=vmlinux,addr=0x80200000 -D log

#根目录下 make debug会进入调试状态  等待gdb链接
debug: vmlinux
	# @qemu-system-riscv64 -nographic -machine virt -kernel vmlinux -S -s -D log
	@qemu-system-riscv64 -nographic -machine virt -bios default -device loader,file=vmlinux,addr=0x80200000 -S -s
clean:
	# ${MAKE} -C init clean
	# ${MAKE} -C lib clean
	${MAKE} -C arch/riscv clean
	$(shell test -f vmlinux && rm vmlinux)
	$(shell test -f System.map && rm System.map)

