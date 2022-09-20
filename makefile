all:
	@nasm -f elf64 -o OS.o OS.asm
	@ld --dynamic-linker=/lib64/ld-linux-x86-64.so.2 -lc OS.o -o OS
	@./OS
clean:
	@echo "Cleaning up Done"
	@rm OS.o
	@rm OS

