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
	.globl	_C
	.data
	.type	_C, @object
	.size	_C, 4
_C:
	.long   7
	.globl	_E
	.data
	.type	_E, @object
	.size	_E, 4
_E:
	.long   5
	.globl	_H
	.data
	.type	_H, @object
	.size	_H, 4
_H:
	.long   2
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
	.globl	_b
	.data
	.type	_b, @object
	.size	_b, 4
_b:
	.long	7
	.section	 .rodata
.LC2:
	.string "\n" 
	.section	 .rodata
.LC3:
	.string "\n" 
	.section	 .rodata
.LC4:
	.string "\n" 
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _A(%rip), %eax
	movl _O(%rip), %edx
	subl %eax, %edx
	movl %edx, __temp0(%rip)
	movl _H(%rip), %eax
	movl _B(%rip), %edx
	imull %eax, %edx
	movl %edx, __temp1(%rip)
	movl __temp1(%rip), %eax
	movl __temp0(%rip), %edx
	subl %eax, %edx
	movl %edx, __temp2(%rip)
	movl __temp2(%rip), %eax
	movl %eax, _b(%rip)
	movl	_b(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _b(%rip), %eax
	movl _E(%rip), %ecx
	cltd
	idivl %ecx
	movl %eax, __temp3(%rip)
	movl	__temp3(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _b(%rip), %eax
	movl _O(%rip), %edx
	subl %eax, %edx
	movl %edx, __temp4(%rip)
	movl __temp4(%rip), %eax
	movl _E(%rip), %ecx
	cltd
	idivl %ecx
	movl %eax, __temp5(%rip)
	movl	__temp5(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_O(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl teste
	.type	teste, @function
teste:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_A(%rip), %eax
	popq	%rbp
	ret
