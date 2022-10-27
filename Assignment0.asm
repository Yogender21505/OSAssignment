global _start
extern printf, scanf

section .text
_start:
	
	mov eax, 0
	lea rdi, [print1]
	call printf
	
	mov eax, 0
	lea rdi, [inputnum]
	lea rsi, [number]
	call scanf
	
	mov eax, 0
	lea rdi, [print2]
	call printf

	mov eax, 0
	lea rdi, [inputstr]
	lea rsi, [string]
	call scanf

	mov eax, 0
	lea rdi, [outnumber]
	mov rsi, [number]
	call printf

	mov eax, 0
	lea rdi, [outstring]
	lea rsi, [string]
	call printf
	
	mov eax, 1
	mov ebx, 0
	int 0x80
	
	


section .data
	print1: db "Enter Number: ", 0
	inputnum: db "%d",0
	print2: db "Enter String: ",0
	inputstr: db "%s",0
	outnumber: db "Number is %d",0x0a,0
	outstring: db "String is %s",0x0a,0

	
section .bss
	number resb 30
	string resb 30
