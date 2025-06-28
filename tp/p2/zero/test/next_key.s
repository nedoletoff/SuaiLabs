	.file	"next_key.c"
	.text
	.globl	next_key
	.type	next_key, @function
next_key:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -20(%rbp)
	movb	$1, -1(%rbp)
	movsbl	-20(%rbp), %edx
	movzbl	-1(%rbp), %eax
	movl	%eax, %ecx
	sarl	%cl, %edx
	movl	%edx, %eax
	movl	%eax, %edi
	movsbl	-20(%rbp), %esi
	movzbl	-1(%rbp), %eax
	movl	$8, %edx
	subl	%eax, %edx
	movl	%esi, %eax
	movl	%edx, %ecx
	sall	%cl, %eax
	orl	%edi, %eax
	movb	%al, -20(%rbp)
	movzbl	-20(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	next_key, .-next_key
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
