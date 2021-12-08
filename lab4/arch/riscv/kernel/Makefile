# makefile_kernel
.PHONY: all clean
all: sched.o head.o entry.o strap.o vm.o

head.o: head.S
	$(GCC) -c -g head.S $(CFLAG)

entry.o: entry.S
	$(GCC) -c -g entry.S $(CFLAG)

strap.o: strap.c
	$(GCC) -c -g strap.c $(CFLAG)

sched.o: sched.c
	$(GCC) -c -g sched.c $(CFLAG)

vm.o : vm.c
	$(GCC) -c -g vm.c $(CFLAG)

clean:
	-rm -f *.o
