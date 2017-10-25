	.file	"div.c"
	.section	.rodata
.LC0:
	.string	"%d."
.LC1:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-128(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -96(%rbp)
	movq	-128(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -92(%rbp)
	movl	-96(%rbp), %eax
	cltd
	idivl	-92(%rbp)
	movl	%eax, -88(%rbp)
	movl	-96(%rbp), %eax
	cltd
	idivl	-92(%rbp)
	movl	%edx, -104(%rbp)
	movl	-88(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -100(%rbp)
	jmp	.L2
.L3:
	movl	-104(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	cltd
	idivl	-92(%rbp)
	movl	%eax, -84(%rbp)
	movl	-100(%rbp), %eax
	cltq
	movl	-84(%rbp), %edx
	movl	%edx, -80(%rbp,%rax,4)
	movl	-104(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	cltd
	idivl	-92(%rbp)
	movl	%edx, -104(%rbp)
	movl	-100(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -100(%rbp)
.L2:
	cmpl	$15, -100(%rbp)
	jle	.L3
	movl	$10, %edi
	call	putchar
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L4
	call	__stack_chk_fail
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
