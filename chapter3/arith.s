	.file	"arith.c"
	.text
	.globl	arith
	.type	arith, @function
arith:
.LFB11:
	.cfi_startproc
	leaq	(%rdi,%rsi), %rax
	addq	%rdx, %rax
	leaq	(%rsi,%rsi,2), %rcx
	salq	$4, %rcx
	leaq	4(%rdi,%rcx), %rcx
	imulq	%rcx, %rax
	ret
	.cfi_endproc
.LFE11:
	.size	arith, .-arith
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
