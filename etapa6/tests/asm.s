	.globl	__temp0
	.data
	.type	__temp0, @object
	.size	__temp0, 4
__temp0:
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
	.globl	_I
	.data
	.type	_I, @object
	.size	_I, 4
_I:
	.long   1
	.globl	_O
	.data
	.type	_O, @object
	.size	_O, 4
_O:
	.long   0
	.globl	_I.B
	.data
	.type	_I.B, @object
	.size	_I.B, 4
_I.B:
	.float  1.8
	.section	.rodata
.LC0:
	.string	"%d"
	.section	.rodata
.LC1:
	.string	"%f"
	.globl	_last
	.data
	.type	_last, @object
	.size	_last, 4
_last:
	.long	1
	.globl	_i
	.data
	.type	_i, @object
	.size	_i, 4
_i:
	.long	0
	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 32
_a:
	.long	0
	.long	9
	.long	8
	.globl	_batata
	.data
	.type	_batata, @object
	.size	_batata, 4
_batata:
	.float	1.8
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
	.string "\nOI\n" 
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _I(%rip), %eax
	cltq
	movl _a(,%rax, 4), %eax
	movl %eax, __temp0(%rip)
	movl	__temp0(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _I(%rip), %eax
	movl _C(%rip), %edx
	cltq
	movl %edx, _a(,%rax, 4)
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _I(%rip), %eax
	cltq
	movl _a(,%rax, 4), %eax
	movl %eax, __temp1(%rip)
	movl	__temp1(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movss	_batata(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	.LC1(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_last(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	popq	%rbp
	ret
