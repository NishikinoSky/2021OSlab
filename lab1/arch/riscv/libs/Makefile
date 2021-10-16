# YOUR MAKEFILE CODE
C_SRC       = $(sort $(wildcard *.c))
#$(patsubst 原模式， 目标模式， 文件列表)
OBJ		    = $(patsubst %.c,%.o,$(C_SRC))

all: $(OBJ) 

%.o:%.c
	${CC}  ${CFLAG}  -c $<

clean:
	$(shell rm *.o 2>/dev/null)
