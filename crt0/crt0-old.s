	.file	"crt0-old.c"
	.text
	.globl	_start
	.type	_start, @function
_start:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$12, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	call	init_libdayos
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	call	_init
	movl	-20(%ebp), %eax
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	%eax
	call	main
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	call	_fini
	subl	$12, %esp
	pushl	-16(%ebp)
	call	exit
	.cfi_endproc
.LFE0:
	.size	_start, .-_start
	.ident	"GCC: (GNU) 5.3.0"
	.section	.note.GNU-stack,"",@progbits
