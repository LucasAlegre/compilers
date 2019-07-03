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
	.long	9
	.globl	_c
	.data
	.type	_c, @object
	.size	_c, 4
_c:
	.long	0
	.globl	_b
	.data
	.type	_b, @object
	.size	_b, 4
_b:
	.long	0
	.globl	_s
	.data
	.type	_s, @object
	.size	_s, 4
_s:
	.long	0
	.globl	_bc
	.data
	.type	_bc, @object
	.size	_bc, 4
_bc:
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
	.globl dosomething
	.type	dosomething, @function
dosomething:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_b(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_O(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl dosomething2
	.type	dosomething2, @function
dosomething2:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_s(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _bc(%rip), %eax
	movl _I(%rip), %edx
	addl %eax, %edx
	movl %edx, __temp0(%rip)
	movl	__temp0(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_O(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _a(%rip), %eax
	movl %eax, _b(%rip)
	call	dosomething
	movl	%eax, __temp1(%rip)
	movl __temp1(%rip), %eax
	movl %eax, _a(%rip)
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_a(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$_c, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl _a(%rip), %eax
	movl %eax, _s(%rip)
	movl _c(%rip), %eax
	movl %eax, _bc(%rip)
	call	dosomething2
	movl	%eax, __temp2(%rip)
	movl	__temp2(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_O(%rip), %eax
	popq	%rbp
	ret
