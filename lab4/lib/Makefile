# makefile_lib
.PHONY: all clean
all: put.o rand.o

put.o: put.c
	$(GCC) -c -g put.c $(CFLAG)
rand.o: rand.c
	$(GCC) -c -g rand.c $(CFLAG)

clean:
	-rm -f *.o
