.data

.text

.global log
log:
	pushl %ebp
	movl %esp, %ebp

	fldln2
	fldl 8(%ebp)
	fyl2x

	popl %ebp
	ret



.global log2
log2:
	pushl %ebp
	movl %esp, %ebp

	fldz
	fldl 8(%ebp)
	fyl2x

	popl %ebp
	ret

.global sin
sin:
  	pushl %ebp
   	movl %esp, %ebp

   	fldl 8(%ebp)
   	fsin

   	popl %ebp
   	ret


.global cos
cos:
   	pushl %ebp
   	movl %esp, %ebp

   	fldl 8(%ebp)
   	fcos

   	popl %ebp
   	ret


.global sqrt
sqrt:
   	pushl %ebp
   	movl %esp, %ebp

   	fldl 8(%ebp)
   	fsqrt

   	popl %ebp
   	ret