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
	.weak	_Z7inithshv
	.type	_Z7inithshv, @function
_Z7inithshv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	n(%rip), %esi
	testl	%esi, %esi
	jle	.L2
	movl	$0, %edx
	movl	$1, %ecx
	leaq	8+in(%rip), %rdi
	leaq	1+s(%rip), %r8
.L4:
	movsbl	(%rdx,%r8), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rdi,%rdx,8)
	addl	$1, %ecx
	addq	$1, %rdx
	cmpl	%esi, %ecx
	jle	.L4
	leaq	8+in(%rip), %rax
	leaq	8+hsh1(%rip), %rdx
	leal	-1(%rsi), %ecx
	leaq	in(%rip), %rdi
	leaq	16(%rdi,%rcx,8), %rdi
.L7:
	imulq	$233, -8(%rdx), %rcx
	addq	(%rax), %rcx
	movq	%rcx, (%rdx)
	addq	$8, %rax
	addq	$8, %rdx
	cmpq	%rdi, %rax
	jne	.L7
.L6:
	movl	%esi, %eax
	leaq	hsh2(%rip), %rdi
	leaq	in(%rip), %r8
.L8:
	movslq	%eax, %rcx
	leal	1(%rax), %edx
	movslq	%edx, %rdx
	imulq	$233, (%rdi,%rdx,8), %rdx
	addq	(%r8,%rcx,8), %rdx
	movq	%rdx, (%rdi,%rcx,8)
	subl	$1, %eax
	jne	.L8
	movq	$1, pows(%rip)
	testl	%esi, %esi
	jle	.L1
	leaq	pows(%rip), %rax
	movl	$1, %edx
.L10:
	imulq	$233, (%rax), %rcx
	movq	%rcx, 8(%rax)
	addl	$1, %edx
	addq	$8, %rax
	cmpl	%esi, %edx
	jle	.L10
.L1:
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L2:
	.cfi_restore_state
	testl	%esi, %esi
	jne	.L6
	movq	$1, pows(%rip)
	jmp	.L1
	.cfi_endproc
.LFE0:
	.size	_Z7inithshv, .-_Z7inithshv
	.section	.text._Z8segment1ii,"axG",@progbits,_Z8segment1ii,comdat
	.weak	_Z8segment1ii
	.type	_Z8segment1ii, @function
_Z8segment1ii:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subl	$1, %edi
	leaq	hsh1(%rip), %rax
	movslq	%esi, %rcx
	subl	%edi, %esi
	movslq	%esi, %rsi
	movslq	%edi, %rdi
	leaq	pows(%rip), %rdx
	movq	(%rdx,%rsi,8), %rdx
	imulq	(%rax,%rdi,8), %rdx
	movq	(%rax,%rcx,8), %rax
	subq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z8segment1ii, .-_Z8segment1ii
	.section	.text._Z8segment2ii,"axG",@progbits,_Z8segment2ii,comdat
	.weak	_Z8segment2ii
	.type	_Z8segment2ii, @function
_Z8segment2ii:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addl	$1, %esi
	leaq	hsh2(%rip), %rcx
	movslq	%edi, %r8
	movl	%esi, %eax
	subl	%edi, %eax
	cltq
	movslq	%esi, %rsi
	leaq	pows(%rip), %rdx
	movq	(%rdx,%rax,8), %rdx
	imulq	(%rcx,%rsi,8), %rdx
	movq	(%rcx,%r8,8), %rax
	subq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_Z8segment2ii, .-_Z8segment2ii
	.section	.text._Z6merge1iiii,"axG",@progbits,_Z6merge1iiii,comdat
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
	subq	$8, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movl	%edx, %r12d
	movl	%ecx, %r13d
	call	_Z8segment1ii
	movl	%r13d, %edx
	subl	%r12d, %edx
	addl	$1, %edx
	movslq	%edx, %rdx
	leaq	pows(%rip), %rcx
	imulq	(%rcx,%rdx,8), %rax
	movq	%rax, %rbx
	movl	%r13d, %esi
	movl	%r12d, %edi
	call	_Z8segment1ii
	addq	%rbx, %rax
	addq	$8, %rsp
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
	subq	$8, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movl	%edi, %r12d
	movl	%esi, %r13d
	movl	%ecx, %esi
	movl	%edx, %edi
	call	_Z8segment2ii
	movl	%r13d, %edx
	subl	%r12d, %edx
	addl	$1, %edx
	movslq	%edx, %rdx
	leaq	pows(%rip), %rcx
	imulq	(%rcx,%rdx,8), %rax
	movq	%rax, %rbx
	movl	%r13d, %esi
	movl	%r12d, %edi
	call	_Z8segment2ii
	addq	%rbx, %rax
	addq	$8, %rsp
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
	pushq	%rbx
	subq	$8, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, %ebx
	movl	%esi, %r12d
	movl	%edx, %r13d
	movl	%ecx, %r14d
	call	_Z6merge1iiii
	movq	%rax, %r15
	movl	%r14d, %ecx
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
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
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
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	leaq	1+s(%rip), %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	scanf@PLT
	leaq	1+s(%rip), %rdi
	movl	$0, %eax
	movq	$-1, %rcx
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	subq	$1, %rax
	movl	%eax, n(%rip)
	call	_Z7inithshv
	movl	n(%rip), %r13d
	testl	%r13d, %r13d
	jle	.L26
	movl	$1, %r15d
	jmp	.L33
.L29:
	addl	$1, %ebx
	cmpl	%r13d, %ebx
	jg	.L28
.L30:
	movl	%ebx, %ecx
	movl	%r12d, %edx
	movl	%r14d, %esi
	movl	%r15d, %edi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L29
	movl	-52(%rbp), %eax
	addl	%ebx, %eax
	cltq
	addq	%rax, ans(%rip)
	jmp	.L29
.L28:
	addl	$1, %r12d
	cmpl	%r13d, %r12d
	jg	.L39
.L31:
	cmpl	%r12d, %r13d
	jl	.L28
	movl	%r12d, %ebx
	movl	-56(%rbp), %eax
	subl	%r12d, %eax
	addl	$2, %eax
	movl	%eax, -52(%rbp)
	jmp	.L30
.L39:
	addl	$1, %r14d
	cmpl	%r13d, %r14d
	jg	.L27
.L32:
	movl	$1, %r12d
	movl	%r14d, %eax
	subl	%r15d, %eax
	movl	%eax, -56(%rbp)
	jmp	.L31
.L27:
	movq	ans(%rip), %rcx
	movabsq	$1229782928473866755, %rax
	mulq	%rcx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$30, %rax
	imulq	$2013265921, %rax, %rax
	subq	%rax, %rcx
	movq	%rcx, ans(%rip)
	addl	$1, %r15d
	cmpl	%r13d, %r15d
	jg	.L26
.L33:
	cmpl	%r15d, %r13d
	jl	.L27
	movl	%r15d, %r14d
	jmp	.L32
.L26:
	movq	ans(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	addq	$24, %rsp
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
