_start:
 	@nasm -f elf64 -o aanchal.o aanchal.asm
 	@ld --dynamic-linker=/lib64/ld-linux-x86-64.so.2 -lc aanchal.o -o aanch
        @./aanch

clear_files:
	rm aanchal.o
	rm aanch
