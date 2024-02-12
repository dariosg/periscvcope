# ToDo Crosscompile with cmake

CC=riscv32-unknown-elf-gcc
LD=riscv32-unknown-elf-ld
CFLAGS=-c -fno-pic -static -fno-builtin -O0

# ensure main is the entry point and that the code starts at address 0
LDFLAGS= -e main -Ttext 0

all: factorial add_array

factorial: factorial.o
	$(LD) $(LDFLAGS) -o $@ $<

add_array: add_array.o
	$(LD) $(LDFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)	

clean:
	rm -rf *.o add_array factorial
