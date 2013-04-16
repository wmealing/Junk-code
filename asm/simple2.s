.section .data

.section .text

.globl _start

_start:
	movl	$100, %ebx
	movl	$1, %eax
	int $0x80
