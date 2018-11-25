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
	movl	n(%rip), %r9d
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	cmpl	$0, %r9d
	jle	.L2
	cmpl	$15, %r9d
	movl	$15, %r10d
	leaq	-8+in(%rip), %rsi
	cmovbe	%r9d, %r10d
	cmpl	$23, %r9d
	leaq	-1+s(%rip), %rdi
	cmovle	%r9d, %r10d
	movl	$2, %eax
	leal	-1(%r10), %ecx
	addq	$3, %rcx
	.p2align 4,,10
	.p2align 3
.L4:
	movsbl	(%rdi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rsi,%rax,8)
	movl	%eax, %edx
	addq	$1, %rax
	cmpq	%rcx, %rax
	jne	.L4
	cmpl	%r10d, %r9d
	leal	-1(%r9), %r8d
	leaq	in(%rip), %rcx
	je	.L5
	movl	%r9d, %ebx
	leal	-1(%r9), %r8d
	movl	%r10d, %eax
	subl	%r10d, %ebx
	leal	-16(%rbx), %r11d
	movl	%r8d, %ecx
	subl	%r10d, %ecx
	shrl	$4, %r11d
	addl	$1, %r11d
	movl	%r11d, %r12d
	sall	$4, %r12d
	cmpl	$14, %ecx
	jbe	.L28
	leaq	s(%rip), %rsi
	leaq	in(%rip), %rcx
	addq	$1, %rax
	pxor	%xmm7, %xmm7
	xorl	%edi, %edi
	pxor	%xmm6, %xmm6
	leaq	(%rsi,%rax), %r10
	pxor	%xmm4, %xmm4
	leaq	(%rcx,%rax,8), %rax
	movdqa	.LC0(%rip), %xmm5
	.p2align 4,,10
	.p2align 3
.L8:
	movdqa	%xmm7, %xmm2
	movdqa	%xmm6, %xmm3
	movdqa	(%r10), %xmm0
	addl	$1, %edi
	movdqa	%xmm6, %xmm8
	addq	$16, %r10
	pcmpgtb	%xmm0, %xmm2
	movdqa	%xmm0, %xmm1
	subq	$-128, %rax
	punpcklbw	%xmm2, %xmm1
	punpckhbw	%xmm2, %xmm0
	pcmpgtw	%xmm1, %xmm3
	movdqa	%xmm1, %xmm2
	pcmpgtw	%xmm0, %xmm8
	punpcklwd	%xmm3, %xmm2
	punpckhwd	%xmm3, %xmm1
	movdqa	%xmm0, %xmm3
	punpckhwd	%xmm8, %xmm0
	punpcklwd	%xmm8, %xmm3
	movdqa	%xmm4, %xmm8
	paddd	%xmm5, %xmm2
	movdqa	%xmm2, %xmm9
	paddd	%xmm5, %xmm1
	pcmpgtd	%xmm2, %xmm8
	paddd	%xmm5, %xmm0
	paddd	%xmm5, %xmm3
	punpckhdq	%xmm8, %xmm2
	punpckldq	%xmm8, %xmm9
	movdqa	%xmm1, %xmm8
	movaps	%xmm2, -112(%rax)
	movdqa	%xmm4, %xmm2
	movaps	%xmm9, -128(%rax)
	pcmpgtd	%xmm1, %xmm2
	punpckhdq	%xmm2, %xmm1
	punpckldq	%xmm2, %xmm8
	movdqa	%xmm3, %xmm2
	movaps	%xmm1, -80(%rax)
	movdqa	%xmm4, %xmm1
	movaps	%xmm8, -96(%rax)
	pcmpgtd	%xmm3, %xmm1
	punpckldq	%xmm1, %xmm2
	punpckhdq	%xmm1, %xmm3
	movdqa	%xmm4, %xmm1
	movaps	%xmm2, -64(%rax)
	pcmpgtd	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	movaps	%xmm3, -48(%rax)
	punpckldq	%xmm1, %xmm2
	punpckhdq	%xmm1, %xmm0
	movaps	%xmm2, -32(%rax)
	movaps	%xmm0, -16(%rax)
	cmpl	%edi, %r11d
	ja	.L8
	addl	%r12d, %edx
	cmpl	%ebx, %r12d
	je	.L5
.L6:
	movslq	%edx, %rdi
	movsbl	(%rsi,%rdi), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rcx,%rdi,8)
	leal	1(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	2(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	3(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	4(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	5(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	6(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	7(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	8(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	9(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	10(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	11(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	12(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	leal	13(%rdx), %eax
	cmpl	%eax, %r9d
	jl	.L5
	cltq
	addl	$14, %edx
	movsbl	(%rsi,%rax), %edi
	subl	$96, %edi
	cmpl	%edx, %r9d
	movslq	%edi, %rdi
	movq	%rdi, (%rcx,%rax,8)
	jl	.L5
	movslq	%edx, %rdx
	movsbl	(%rsi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rcx,%rdx,8)
.L5:
	movq	hsh1(%rip), %rdx
	movl	%r8d, %eax
	leaq	hsh1(%rip), %rdi
	leaq	16(,%rax,8), %rsi
	movl	$8, %eax
	.p2align 4,,10
	.p2align 3
.L14:
	imulq	$233, %rdx, %rdx
	addq	(%rcx,%rax), %rdx
	movq	%rdx, (%rdi,%rax)
	addq	$8, %rax
	cmpq	%rsi, %rax
	jne	.L14
.L13:
	movslq	%r9d, %rsi
	leaq	hsh2(%rip), %r10
	movl	%r8d, %r11d
	salq	$3, %rsi
	movq	%r11, %r8
	xorl	%eax, %eax
	movq	8(%r10,%rsi), %rdx
	notq	%r8
	salq	$3, %r8
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	(%rcx,%rax), %rdi
	imulq	$233, %rdx, %rdx
	addq	(%rdi,%rsi), %rdx
	leaq	(%r10,%rax), %rdi
	subq	$8, %rax
	cmpq	%r8, %rax
	movq	%rdx, (%rdi,%rsi)
	jne	.L12
	testl	%r9d, %r9d
	movq	$1, pows(%rip)
	jle	.L1
	leaq	pows(%rip), %rdx
	leaq	8+pows(%rip), %rax
	leaq	16(%rdx,%r11,8), %rcx
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L16:
	imulq	$233, %rdx, %rdx
	addq	$8, %rax
	movq	%rdx, -8(%rax)
	cmpq	%rcx, %rax
	jne	.L16
.L1:
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L28:
	.cfi_restore_state
	leaq	s(%rip), %rsi
	leaq	in(%rip), %rcx
	jmp	.L6
.L2:
	jne	.L29
	movq	$1, pows(%rip)
	jmp	.L1
.L29:
	leal	-1(%r9), %r8d
	leaq	in(%rip), %rcx
	jmp	.L13
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
.LC1:
	.string	"%s"
.LC2:
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
	leaq	.LC1(%rip), %rdi
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
	jle	.L42
	leal	1(%rax), %r13d
	movl	$1, -52(%rbp)
.L48:
	movl	-52(%rbp), %r14d
.L47:
	movl	%r14d, %eax
	subl	-52(%rbp), %eax
	movl	$1, %ebx
	movl	%eax, -64(%rbp)
	.p2align 4,,10
	.p2align 3
.L46:
	cmpl	-60(%rbp), %ebx
	jg	.L43
	movl	-64(%rbp), %eax
	movl	%ebx, %r15d
	subl	%ebx, %eax
	addl	$2, %eax
	movl	%eax, -56(%rbp)
	.p2align 4,,10
	.p2align 3
.L45:
	movl	-52(%rbp), %edi
	movl	%r15d, %ecx
	movl	%ebx, %edx
	movl	%r14d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L44
	movl	-56(%rbp), %eax
	addl	%r15d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L44:
	addl	$1, %r15d
	cmpl	%r13d, %r15d
	jne	.L45
.L43:
	addl	$1, %ebx
	cmpl	%r13d, %ebx
	jne	.L46
	addl	$1, %r14d
	cmpl	%r14d, -60(%rbp)
	jge	.L47
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
	jne	.L48
.L42:
	leaq	.LC2(%rip), %rdi
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
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	-96
	.long	-96
	.long	-96
	.long	-96
	.ident	"GCC: (Debian 6.4.0-2) 6.4.0 20170724"
	.section	.note.GNU-stack,"",@progbits
