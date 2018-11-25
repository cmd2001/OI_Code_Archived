	.file	"t3_30pts.cpp"
	.section	.rodata
	.align 4
	.type	_ZL4maxn, @object
	.size	_ZL4maxn, 4
_ZL4maxn:
	.long	1100
	.align 8
	.type	_ZL4base, @object
	.size	_ZL4base, 8
_ZL4base:
	.quad	233
	.align 8
	.type	_ZL3mod, @object
	.size	_ZL3mod, 8
_ZL3mod:
	.quad	2013265921
	.globl	s
	.bss
	.align 32
	.type	s, @object
	.size	s, 1100
s:
	.zero	1100
	.globl	in
	.align 32
	.type	in, @object
	.size	in, 8800
in:
	.zero	8800
	.globl	hsh1
	.align 32
	.type	hsh1, @object
	.size	hsh1, 8800
hsh1:
	.zero	8800
	.globl	hsh2
	.align 32
	.type	hsh2, @object
	.size	hsh2, 8800
hsh2:
	.zero	8800
	.globl	pows
	.align 32
	.type	pows, @object
	.size	pows, 8800
pows:
	.zero	8800
	.globl	ans
	.align 8
	.type	ans, @object
	.size	ans, 8
ans:
	.zero	8
	.globl	n
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.zero	4
	.section	.text._Z7inithshv,"axG",@progbits,_Z7inithshv,comdat
	.p2align 4,,15
	.weak	_Z7inithshv
	.type	_Z7inithshv, @function
_Z7inithshv:
.LFB0:
	.cfi_startproc
	movl	n(%rip), %edi
	cmpl	$0, %edi
	jle	.L2
	leal	-1(%rdi), %ecx
	leaq	in(%rip), %rsi
	leaq	s(%rip), %r8
	movl	$1, %edx
	movq	%rcx, %r9
	addq	$2, %rcx
	.p2align 4,,10
	.p2align 3
.L4:
	movsbl	(%r8,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
	cmpq	%rcx, %rdx
	jne	.L4
	leaq	8+in(%rip), %rax
	leaq	8+hsh1(%rip), %rcx
	leaq	(%rsi,%rdx,8), %r8
	.p2align 4,,10
	.p2align 3
.L8:
	imulq	$233, -8(%rcx), %rdx
	addq	$8, %rax
	addq	$8, %rcx
	addq	-8(%rax), %rdx
	movq	%rdx, -8(%rcx)
	cmpq	%r8, %rax
	jne	.L8
.L7:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leal	1(%rdi), %r10d
	xorl	%eax, %eax
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	leaq	1(%r9), %rbx
	movslq	%r10d, %r10
	leaq	hsh2(%rip), %r12
	salq	$3, %r10
	movq	%rbx, %r11
	leaq	-8(%r10), %r8
	negq	%r11
	salq	$3, %r11
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	(%r12,%rax), %rcx
	leaq	(%rsi,%rax), %r9
	subq	$8, %rax
	imulq	$233, (%rcx,%r10), %rdx
	addq	(%r9,%r8), %rdx
	cmpq	%rax, %r11
	movq	%rdx, (%rcx,%r8)
	jne	.L6
	testl	%edi, %edi
	movq	$1, pows(%rip)
	jle	.L1
	leaq	pows(%rip), %rdx
	leaq	8+pows(%rip), %rax
	leaq	(%rdx,%rbx,8), %rcx
	movl	$1, %edx
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L18:
	addq	$8, %rax
.L10:
	imulq	$233, %rdx, %rdx
	cmpq	%rcx, %rax
	movq	%rdx, (%rax)
	jne	.L18
.L1:
	popq	%rbx
	.cfi_restore 3
	popq	%r12
	.cfi_restore 12
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa 7, 8
	ret
.L2:
	jne	.L19
	movq	$1, pows(%rip)
	ret
.L19:
	leal	-1(%rdi), %r9d
	leaq	in(%rip), %rsi
	jmp	.L7
	.cfi_endproc
.LFE0:
	.size	_Z7inithshv, .-_Z7inithshv
	.section	.text._Z8segment1ii,"axG",@progbits,_Z8segment1ii,comdat
	.p2align 4,,15
	.weak	_Z8segment1ii
	.type	_Z8segment1ii, @function
_Z8segment1ii:
.LFB1:
	.cfi_startproc
	subl	$1, %edi
	leaq	hsh1(%rip), %rax
	movslq	%esi, %rcx
	leaq	pows(%rip), %rdx
	subl	%edi, %esi
	movslq	%edi, %rdi
	movslq	%esi, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdx,%rsi,8), %rdx
	imulq	(%rax,%rdi,8), %rdx
	movq	(%rax,%rcx,8), %rax
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	popq	%rbp
	.cfi_def_cfa 7, 8
	subq	%rdx, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	_Z8segment1ii, .-_Z8segment1ii
	.section	.text._Z8segment2ii,"axG",@progbits,_Z8segment2ii,comdat
	.p2align 4,,15
	.weak	_Z8segment2ii
	.type	_Z8segment2ii, @function
_Z8segment2ii:
.LFB2:
	.cfi_startproc
	addl	$1, %esi
	leaq	hsh2(%rip), %rcx
	leaq	pows(%rip), %rdx
	movl	%esi, %eax
	movslq	%esi, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	subl	%edi, %eax
	movslq	%edi, %r8
	cltq
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	(%rdx,%rax,8), %rdx
	movq	(%rcx,%r8,8), %rax
	imulq	(%rcx,%rsi,8), %rdx
	popq	%rbp
	.cfi_def_cfa 7, 8
	subq	%rdx, %rax
	ret
	.cfi_endproc
.LFE2:
	.size	_Z8segment2ii, .-_Z8segment2ii
	.section	.text._Z6merge1iiii,"axG",@progbits,_Z6merge1iiii,comdat
	.p2align 4,,15
	.weak	_Z6merge1iiii
	.type	_Z6merge1iiii, @function
_Z6merge1iiii:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movl	%ecx, %r13d
	movl	%edx, %r12d
	subq	$8, %rsp
	call	_Z8segment1ii
	movl	%r13d, %esi
	leaq	pows(%rip), %rdx
	movl	%r12d, %edi
	subl	%r12d, %esi
	addl	$1, %esi
	movslq	%esi, %rsi
	imulq	(%rdx,%rsi,8), %rax
	movl	%r13d, %esi
	movq	%rax, %rbx
	call	_Z8segment1ii
	addq	$8, %rsp
	addq	%rbx, %rax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_Z6merge1iiii, .-_Z6merge1iiii
	.section	.text._Z6merge2iiii,"axG",@progbits,_Z6merge2iiii,comdat
	.p2align 4,,15
	.weak	_Z6merge2iiii
	.type	_Z6merge2iiii, @function
_Z6merge2iiii:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movl	%edi, %r12d
	movl	%esi, %r13d
	movl	%edx, %edi
	movl	%ecx, %esi
	subq	$8, %rsp
	call	_Z8segment2ii
	movl	%r13d, %edx
	leaq	pows(%rip), %rcx
	movl	%r13d, %esi
	subl	%r12d, %edx
	movl	%r12d, %edi
	addl	$1, %edx
	movslq	%edx, %rdx
	imulq	(%rcx,%rdx,8), %rax
	movq	%rax, %rbx
	call	_Z8segment2ii
	addq	$8, %rsp
	addq	%rbx, %rax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	_Z6merge2iiii, .-_Z6merge2iiii
	.section	.text._Z5judgeiiii,"axG",@progbits,_Z5judgeiiii,comdat
	.p2align 4,,15
	.weak	_Z5judgeiiii
	.type	_Z5judgeiiii, @function
_Z5judgeiiii:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	movl	%edx, %r13d
	pushq	%rbx
	movl	%esi, %r12d
	.cfi_offset 3, -56
	movl	%edi, %ebx
	movl	%ecx, %r14d
	subq	$8, %rsp
	call	_Z6merge1iiii
	movl	%r14d, %ecx
	movq	%rax, %r15
	movl	%r13d, %edx
	movl	%r12d, %esi
	movl	%ebx, %edi
	call	_Z6merge2iiii
	cmpq	%rax, %r15
	sete	%al
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z5judgeiiii, .-_Z5judgeiiii
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s"
.LC1:
	.string	"%llu\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	1+s(%rip), %rsi
	leaq	.LC0(%rip), %rdi
	xorl	%eax, %eax
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	call	scanf@PLT
	leaq	1+s(%rip), %rdi
	call	strlen@PLT
	movl	%eax, n(%rip)
	call	_Z7inithshv
	movl	n(%rip), %eax
	movq	ans(%rip), %r12
	testl	%eax, %eax
	movl	%eax, -60(%rbp)
	jle	.L32
	movl	-60(%rbp), %eax
	movl	$1, -52(%rbp)
	leal	1(%rax), %r13d
.L38:
	movl	-52(%rbp), %r14d
.L37:
	movl	%r14d, %eax
	subl	-52(%rbp), %eax
	movl	$1, %ebx
	movl	%eax, -64(%rbp)
	.p2align 4,,10
	.p2align 3
.L36:
	cmpl	-60(%rbp), %ebx
	jg	.L33
	movl	-64(%rbp), %eax
	movl	%ebx, %r15d
	subl	%ebx, %eax
	addl	$2, %eax
	movl	%eax, -56(%rbp)
	.p2align 4,,10
	.p2align 3
.L35:
	movl	-52(%rbp), %edi
	movl	%r15d, %ecx
	movl	%ebx, %edx
	movl	%r14d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L34
	movl	-56(%rbp), %eax
	addl	%r15d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L34:
	addl	$1, %r15d
	cmpl	%r13d, %r15d
	jne	.L35
.L33:
	addl	$1, %ebx
	cmpl	%r13d, %ebx
	jne	.L36
	addl	$1, %r14d
	cmpl	%r14d, -60(%rbp)
	jge	.L37
	movabsq	$1229782928473866755, %rax
	addl	$1, -52(%rbp)
	mulq	%r12
	movq	%r12, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$30, %rax
	imulq	$2013265921, %rax, %rax
	subq	%rax, %r12
	movl	-52(%rbp), %eax
	movq	%r12, ans(%rip)
	cmpl	%eax, %r13d
	jne	.L38
.L32:
	leaq	.LC1(%rip), %rdi
	movq	%r12, %rsi
	xorl	%eax, %eax
	call	printf@PLT
	addq	$24, %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 6.4.0-2) 6.4.0 20170724"
	.section	.note.GNU-stack,"",@progbits
