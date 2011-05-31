#PURPOSE: Simple program that exits and returns a
# status code back to the Linux kernel
# 

#INPUT: none
# 

#OUTPUT: returns a status code.
# This can be viewed
# echo $?

#Chapter 3. Your First Programs

.section .data

.section .text

.globl _start

_start:
	movl $1, %eax
	# this is the linux kernel command
	# number (system call) for exiting
	# a program
	movl $0, %ebx 

	int $0x80 # this wakes up the 

