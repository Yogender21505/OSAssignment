global _start
extern printf, scanf

section .text
_start:
	
	mov eax, 0
	lea rdi, [printinteger]
	call printf
	
	mov eax, 0
	lea rdi, [inputnum]
	lea rsi, [number]
	call scanf

	mov eax, 0
	lea rdi , [printstring]
	call printf
	
	mov eax, 0
	lea rdi, [inputstring]
	lea rsi, [string]
	call scanf
	
	
	lea rdi, [printoutnum]
	mov rsi, [number]
	mov eax, 0
	call printf

	lea rdi, [printoutstr]
	lea rsi, [string]
	mov eax, 0
	call printf
	
	mov rax, 1
	mov rbx, 0
	int 0x80

section .data
	printinteger: db "Enter the Number: ",0
	inputnum: db "%d",0
	printstring: db "Enter the String: ",0
	inputstring: db "%s",0
	printoutnum: db "Number is %d",0x0a,0
	printoutstr: db "String is %s",0x0a,0
section .bss
	number resb  20
	string resb 20
	
