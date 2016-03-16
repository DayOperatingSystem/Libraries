.text

.globl _start
_start:
	pushl %ebp
	movl %esp, %ebp
	
	## Take some memory from stack
	subl $24, %esp
	subl $12, %esp
	
	leal -20(%ebp), %eax
	pushl %eax
	call init_libdayos ## argv = init_libdayos(&argc)
	addl $16, %esp
	movl %eax, -12(%ebp)
	
	call _init
	
	movl -20(%ebp), %eax
	subl $8, %esp
	pushl -12(%ebp)
	pushl %eax
	call main
	addl $16, %esp
	movl %eax, -16(%ebp)
	
	call _fini
	subl $12, %esp
	
	pushl -16(%ebp)
	call exit


 
