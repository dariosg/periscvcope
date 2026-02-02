# ToDo Crosscompile with cmake

CC=riscv32-unknown-elf-gcc
LD=riscv32-unknown-elf-ld
OBJDUMP=riscv32-unknown-elf-objdump

CFLAGS=  -march=rv32i -mabi=ilp32 -c -fno-pic -static -fno-builtin -O0
CPPFLAGS = -I./include


# ensure main is the entry point and that the code starts at address 0
LDFLAGS= -e main -Ttext 0

.PHONY: all clean dump

examples: factorial add_array insertion_sort matrix_multiplication
dump: factorial.dump add_array.dump insertion_sort.dump matrix_multiplication.dump
all: $(examples)

factorial: factorial.o soft_mul.o
	$(LD) $(LDFLAGS) -o $@ $^

add_array: add_array.o
	$(LD) $(LDFLAGS) -o $@ $<

insertion_sort: insertion_sort.o
	$(LD) $(LDFLAGS) -o $@ $<

matrix_multiplication: matrix_multiplication.o soft_mul.o
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS) 

clean:
	rm -rf *.o $(examples) $(dump)

%.dump: %
	$(OBJDUMP) -d $< > $@
