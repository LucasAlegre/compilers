	.globl	__temp4
	.data
	.type	__temp4, @object
	.size	__temp4, 4
__temp4:
	.long  0
	.globl	__temp2
	.data
	.type	__temp2, @object
	.size	__temp2, 4
__temp2:
	.long  0
	.globl	__temp0
	.data
	.type	__temp0, @object
	.size	__temp0, 4
__temp0:
	.long  0
	.globl	__temp7
	.data
	.type	__temp7, @object
	.size	__temp7, 4
__temp7:
	.long  0
	.globl	__temp5
	.data
	.type	__temp5, @object
	.size	__temp5, 4
__temp5:
	.long  0
	.globl	__temp3
	.data
	.type	__temp3, @object
	.size	__temp3, 4
__temp3:
	.long  0
	.globl	__temp1
	.data
	.type	__temp1, @object
	.size	__temp1, 4
__temp1:
	.long  0
	.globl	__temp6
	.data
	.type	__temp6, @object
	.size	__temp6, 4
__temp6:
	.long  0
	.globl	_A
	.data
	.type	_A, @object
	.size	_A, 4
_A:
	.long   9
	.globl	_B
	.data
	.type	_B, @object
	.size	_B, 4
_B:
	.long   8
	.globl	_O
	.data
	.type	_O, @object
	.size	_O, 4
_O:
	.long   0
	.section	.rodata
.LC0:
	.string	"%d"
	.section	.rodata
.LC1:
	.string	"%f"
	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:
	.long	0
	.section	 .rodata
.LC2:
	.string "\n" 
	.section	 .rodata
.LC3:
	.string "\n" 
	.section	 .rodata
.LC4:
	.string "\n" 
	.section	 .rodata
.LC5:
	.string "\n" 
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _A(%rip), %eax
	movl _O(%rip), %edx
	cmpl %eax, %edx
	jge .BL0
	movl $0, %eax
	jmp .BL1
.BL0:
	movl $1, %eax
.BL1:
	movl %eax, __temp0(%rip)
	movl _O(%rip), %eax
	movl _A(%rip), %edx
	cmpl %eax, %edx
	jge .BL2
	movl $0, %eax
	jmp .BL3
.BL2:
	movl $1, %eax
.BL3:
	movl %eax, __temp1(%rip)
	movl __temp0(%rip), %eax
	movl __temp1(%rip), %edx
	andl %eax, %edx
	jz .BL4
	movl $1, %eax
	jmp .BL5
.BL4:
	movl $0, %eax
.BL5:
	movl %eax, __temp2(%rip)
	movl	__temp2(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _A(%rip), %eax
	movl _O(%rip), %edx
	cmpl %eax, %edx
	jge .BL6
	movl $0, %eax
	jmp .BL7
.BL6:
	movl $1, %eax
.BL7:
	movl %eax, __temp3(%rip)
	movl _B(%rip), %eax
	movl _O(%rip), %edx
	cmpl %eax, %edx
	jge .BL8
	movl $0, %eax
	jmp .BL9
.BL8:
	movl $1, %eax
.BL9:
	movl %eax, __temp4(%rip)
	movl __temp3(%rip), %eax
	movl __temp4(%rip), %edx
	andl %eax, %edx
	jz .BL10
	movl $1, %eax
	jmp .BL11
.BL10:
	movl $0, %eax
.BL11:
	movl %eax, __temp5(%rip)
	movl	__temp5(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _A(%rip), %eax
	movl _B(%rip), %edx
	cmpl %eax, %edx
	jge .BL12
	movl $0, %eax
	jmp .BL13
.BL12:
	movl $1, %eax
.BL13:
	movl %eax, __temp6(%rip)
	movl	__temp6(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _B(%rip), %eax
	movl _B(%rip), %edx
	cmpl %eax, %edx
	jge .BL14
	movl $0, %eax
	jmp .BL15
.BL14:
	movl $1, %eax
.BL15:
	movl %eax, __temp7(%rip)
	movl	__temp7(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	popq	%rbp
	ret
