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
	movl	$1, -4(%rbp)
.L3:
	movl	n(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jg	.L2
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	leaq	s(%rip), %rax
	movzbl	(%rdx,%rax), %eax
	movsbl	%al, %eax
	subl	$96, %eax
	movslq	%eax, %rdx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	in(%rip), %rax
	movq	%rdx, (%rcx,%rax)
	addl	$1, -4(%rbp)
	jmp	.L3
.L2:
	movl	$1, -8(%rbp)
.L5:
	movl	n(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jg	.L4
	movl	-8(%rbp), %eax
	subl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh1(%rip), %rax
	movq	(%rdx,%rax), %rax
	imulq	$233, %rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	in(%rip), %rax
	movq	(%rcx,%rax), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh1(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	addl	$1, -8(%rbp)
	jmp	.L5
.L4:
	movl	n(%rip), %eax
	movl	%eax, -12(%rbp)
.L7:
	cmpl	$0, -12(%rbp)
	je	.L6
	movl	-12(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh2(%rip), %rax
	movq	(%rdx,%rax), %rax
	imulq	$233, %rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	in(%rip), %rax
	movq	(%rcx,%rax), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh2(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	subl	$1, -12(%rbp)
	jmp	.L7
.L6:
	movq	$1, pows(%rip)
	movl	$1, -16(%rbp)
.L9:
	movl	n(%rip), %eax
	cmpl	%eax, -16(%rbp)
	jg	.L10
	movl	-16(%rbp), %eax
	subl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	pows(%rip), %rax
	movq	(%rdx,%rax), %rax
	imulq	$233, %rax, %rdx
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	pows(%rip), %rax
	movq	%rdx, (%rcx,%rax)
	addl	$1, -16(%rbp)
	jmp	.L9
.L10:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
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
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	subl	$1, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh1(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	hsh1(%rip), %rax
	movq	(%rcx,%rax), %rcx
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rsi
	leaq	pows(%rip), %rax
	movq	(%rsi,%rax), %rax
	imulq	%rcx, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
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
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	hsh2(%rip), %rax
	movq	(%rdx,%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	hsh2(%rip), %rax
	movq	(%rcx,%rax), %rcx
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rsi
	leaq	pows(%rip), %rax
	movq	(%rsi,%rax), %rax
	imulq	%rcx, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
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
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z8segment1ii
	movq	%rax, %rcx
	movl	-32(%rbp), %eax
	subl	-28(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	pows(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rcx, %rbx
	imulq	%rax, %rbx
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z8segment1ii
	addq	%rbx, %rax
	addq	$24, %rsp
	popq	%rbx
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
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z8segment2ii
	movq	%rax, %rcx
	movl	-24(%rbp), %eax
	subl	-20(%rbp), %eax
	addl	$1, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	pows(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rcx, %rbx
	imulq	%rax, %rbx
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	_Z8segment2ii
	addq	%rbx, %rax
	addq	$24, %rsp
	popq	%rbx
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
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	-32(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-24(%rbp), %esi
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	_Z6merge1iiii
	movq	%rax, %rbx
	movl	-32(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-24(%rbp), %esi
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	_Z6merge2iiii
	cmpq	%rax, %rbx
	sete	%al
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z5judgeiiii, .-_Z5judgeiiii
	.section	.rodata
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
	subq	$16, %rsp
	leaq	1+s(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	scanf@PLT
	leaq	1+s(%rip), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, n(%rip)
	call	_Z7inithshv
	movl	$1, -4(%rbp)
.L30:
	movl	n(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jg	.L22
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
.L29:
	movl	n(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jg	.L23
	movl	$1, -12(%rbp)
.L28:
	movl	n(%rip), %eax
	cmpl	%eax, -12(%rbp)
	jg	.L24
	movl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
.L27:
	movl	n(%rip), %eax
	cmpl	%eax, -16(%rbp)
	jg	.L25
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %esi
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L26
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	movl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	subl	-12(%rbp), %eax
	addl	$2, %eax
	movslq	%eax, %rdx
	movq	ans(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, ans(%rip)
.L26:
	addl	$1, -16(%rbp)
	jmp	.L27
.L25:
	addl	$1, -12(%rbp)
	jmp	.L28
.L24:
	addl	$1, -8(%rbp)
	jmp	.L29
.L23:
	movq	ans(%rip), %rcx
	movabsq	$1229782928473866755, %rdx
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rcx, %rax
	subq	%rdx, %rax
	shrq	%rax
	addq	%rdx, %rax
	shrq	$30, %rax
	imulq	$2013265921, %rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	%rax, ans(%rip)
	addl	$1, -4(%rbp)
	jmp	.L30
.L22:
	movq	ans(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 6.4.0-2) 6.4.0 20170724"
	.section	.note.GNU-stack,"",@progbits
