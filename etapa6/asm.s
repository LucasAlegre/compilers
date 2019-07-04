	.globl	__temp4
	.data
	.type	__temp4, @object
	.size	__temp4, 4
__temp4:
	.long  0
	.globl	__temp10
	.data
	.type	__temp10, @object
	.size	__temp10, 4
__temp10:
	.long  0
	.globl	__temp14
	.data
	.type	__temp14, @object
	.size	__temp14, 4
__temp14:
	.long  0
	.globl	__temp2
	.data
	.type	__temp2, @object
	.size	__temp2, 4
__temp2:
	.long  0
	.globl	__temp9
	.data
	.type	__temp9, @object
	.size	__temp9, 4
__temp9:
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
	.globl	__temp13
	.data
	.type	__temp13, @object
	.size	__temp13, 4
__temp13:
	.long  0
	.globl	__temp17
	.data
	.type	__temp17, @object
	.size	__temp17, 4
__temp17:
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
	.globl	__temp12
	.data
	.type	__temp12, @object
	.size	__temp12, 4
__temp12:
	.long  0
	.globl	__temp16
	.data
	.type	__temp16, @object
	.size	__temp16, 4
__temp16:
	.long  0
	.globl	__temp1
	.data
	.type	__temp1, @object
	.size	__temp1, 4
__temp1:
	.long  0
	.globl	__temp8
	.data
	.type	__temp8, @object
	.size	__temp8, 4
__temp8:
	.long  0
	.globl	__temp11
	.data
	.type	__temp11, @object
	.size	__temp11, 4
__temp11:
	.long  0
	.globl	__temp15
	.data
	.type	__temp15, @object
	.size	__temp15, 4
__temp15:
	.long  0
	.globl	__temp6
	.data
	.type	__temp6, @object
	.size	__temp6, 4
__temp6:
	.long  0
	.globl	_F
	.data
	.type	_F, @object
	.size	_F, 4
_F:
	.long   4
	.globl	_G
	.data
	.type	_G, @object
	.size	_G, 4
_G:
	.long   3
	.globl	_H
	.data
	.type	_H, @object
	.size	_H, 4
_H:
	.long   2
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
	.globl	_op
	.data
	.type	_op, @object
	.size	_op, 4
_op:
	.long	0
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
	.long	0
	.globl	_i
	.data
	.type	_i, @object
	.size	_i, 4
_i:
	.long	0
	.globl	_tmp
	.data
	.type	_tmp, @object
	.size	_tmp, 4
_tmp:
	.long	0
	.globl	_x
	.data
	.type	_x, @object
	.size	_x, 4
_x:
	.long	0
	.globl	_y
	.data
	.type	_y, @object
	.size	_y, 4
_y:
	.long	0
	.globl	_c
	.data
	.type	_c, @object
	.size	_c, 4
_c:
	.long	0
	.globl	_d
	.data
	.type	_d, @object
	.size	_d, 4
_d:
	.long	0
	.globl	_e
	.data
	.type	_e, @object
	.size	_e, 4
_e:
	.long	0
	.globl	_f
	.data
	.type	_f, @object
	.size	_f, 4
_f:
	.long	0
	.globl	_g
	.data
	.type	_g, @object
	.size	_g, 4
_g:
	.long	0
	.globl	_h
	.data
	.type	_h, @object
	.size	_h, 4
_h:
	.long	0
	.globl	_z
	.data
	.type	_z, @object
	.size	_z, 4
_z:
	.long	0
	.section	 .rodata
.LC2:
	.string "\n" 
	.text
	.globl add
	.type	add, @function
add:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _x(%rip), %eax
	movl _y(%rip), %edx
	addl %eax, %edx
	movl %edx, __temp0(%rip)
	movl	__temp0(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl div
	.type	div, @function
div:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _c(%rip), %eax
	movl _d(%rip), %ecx
	cltd
	idivl %ecx
	movl %eax, __temp1(%rip)
	movl	__temp1(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl mul
	.type	mul, @function
mul:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _e(%rip), %eax
	movl _f(%rip), %edx
	imull %eax, %edx
	movl %edx, __temp2(%rip)
	movl	__temp2(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl sub
	.type	sub, @function
sub:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _h(%rip), %eax
	movl _g(%rip), %edx
	subl %eax, %edx
	movl %edx, __temp3(%rip)
	movl	__temp3(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl fat
	.type	fat, @function
fat:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _z(%rip), %eax
	movl %eax, _tmp(%rip)
._label0:
	movl _I(%rip), %eax
	movl _tmp(%rip), %edx
	cmpl %eax, %edx
	jne .BL0
	movl $0, %eax
	jmp .BL1
.BL0:
	movl $1, %eax
.BL1:
	movl %eax, __temp4(%rip)
	movl __temp4(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label1
	movl _I(%rip), %eax
	movl _tmp(%rip), %edx
	subl %eax, %edx
	movl %edx, __temp5(%rip)
	movl __temp5(%rip), %eax
	movl %eax, _tmp(%rip)
	movl _z(%rip), %eax
	movl _tmp(%rip), %edx
	imull %eax, %edx
	movl %edx, __temp6(%rip)
	movl __temp6(%rip), %eax
	movl %eax, _z(%rip)
	jmp ._label0
._label1:
	movl	_z(%rip), %eax
	popq	%rbp
	ret
	.text
	.globl main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
._label2:
	movl _I(%rip), %eax
	movl _I(%rip), %edx
	cmpl %eax, %edx
	je .BL2
	movl $0, %eax
	jmp .BL3
.BL2:
	movl $1, %eax
.BL3:
	movl %eax, __temp7(%rip)
	movl __temp7(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label8
	movl	$_a, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movl	$_b, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movl	$_op, %esi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movl _O(%rip), %eax
	movl _op(%rip), %edx
	cmpl %eax, %edx
	je .BL4
	movl $0, %eax
	jmp .BL5
.BL4:
	movl $1, %eax
.BL5:
	movl %eax, __temp8(%rip)
	movl __temp8(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label3
	movl _a(%rip), %eax
	movl %eax, _x(%rip)
	movl _b(%rip), %eax
	movl %eax, _y(%rip)
	call	add
	movl	%eax, __temp9(%rip)
	movl	__temp9(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
._label3:
	movl _I(%rip), %eax
	movl _op(%rip), %edx
	cmpl %eax, %edx
	je .BL6
	movl $0, %eax
	jmp .BL7
.BL6:
	movl $1, %eax
.BL7:
	movl %eax, __temp10(%rip)
	movl __temp10(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label4
	movl _a(%rip), %eax
	movl %eax, _g(%rip)
	movl _b(%rip), %eax
	movl %eax, _h(%rip)
	call	sub
	movl	%eax, __temp11(%rip)
	movl	__temp11(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
._label4:
	movl _H(%rip), %eax
	movl _op(%rip), %edx
	cmpl %eax, %edx
	je .BL8
	movl $0, %eax
	jmp .BL9
.BL8:
	movl $1, %eax
.BL9:
	movl %eax, __temp12(%rip)
	movl __temp12(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label5
	movl _a(%rip), %eax
	movl %eax, _e(%rip)
	movl _b(%rip), %eax
	movl %eax, _f(%rip)
	call	mul
	movl	%eax, __temp13(%rip)
	movl	__temp13(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
._label5:
	movl _G(%rip), %eax
	movl _op(%rip), %edx
	cmpl %eax, %edx
	je .BL10
	movl $0, %eax
	jmp .BL11
.BL10:
	movl $1, %eax
.BL11:
	movl %eax, __temp14(%rip)
	movl __temp14(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label6
	movl _a(%rip), %eax
	movl %eax, _c(%rip)
	movl _b(%rip), %eax
	movl %eax, _d(%rip)
	call	div
	movl	%eax, __temp15(%rip)
	movl	__temp15(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
._label6:
	movl _F(%rip), %eax
	movl _op(%rip), %edx
	cmpl %eax, %edx
	je .BL12
	movl $0, %eax
	jmp .BL13
.BL12:
	movl $1, %eax
.BL13:
	movl %eax, __temp16(%rip)
	movl __temp16(%rip), %eax
	movl $1, %edx
	andl %eax, %edx
	jz ._label7
	movl _a(%rip), %eax
	movl %eax, _z(%rip)
	call	fat
	movl	%eax, __temp17(%rip)
	movl	__temp17(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
._label7:
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp ._label2
._label8:
	movl	_O(%rip), %eax
	popq	%rbp
	ret
