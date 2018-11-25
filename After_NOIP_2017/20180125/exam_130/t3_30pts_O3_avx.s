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
	.local	s
	.comm	s,1100,32
	.local	in
	.comm	in,8800,32
	.local	hsh1
	.comm	hsh1,8800,32
	.local	hsh2
	.comm	hsh2,8800,32
	.local	pows
	.comm	pows,8800,32
	.local	ans
	.comm	ans,8,8
	.local	n
	.comm	n,4,4
	.text
	.p2align 4,,15
	.type	_Z7inithshv, @function
_Z7inithshv:
.LFB0:
	.cfi_startproc
	movl	n(%rip), %r8d
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	cmpl	$0, %r8d
	jle	.L2
	cmpl	$15, %r8d
	movl	$15, %r10d
	movsbl	1+s(%rip), %eax
	cmovbe	%r8d, %r10d
	cmpl	$23, %r8d
	movl	$3, %edx
	cmovle	%r8d, %r10d
	leaq	-8+in(%rip), %rsi
	leaq	-1+s(%rip), %rdi
	leal	-1(%r10), %ecx
	movl	$2, %r9d
	subl	$96, %eax
	leaq	3(%rcx), %r11
	cltq
	andl	$7, %ecx
	movq	%rax, 8+in(%rip)
	cmpq	%r11, %rdx
	je	.L166
	testq	%rcx, %rcx
	je	.L4
	cmpq	$1, %rcx
	je	.L131
	cmpq	$2, %rcx
	je	.L132
	cmpq	$3, %rcx
	je	.L133
	cmpq	$4, %rcx
	je	.L134
	cmpq	$5, %rcx
	je	.L135
	cmpq	$6, %rcx
	je	.L136
	movsbl	2+s(%rip), %eax
	movl	$4, %edx
	subl	$96, %eax
	cltq
	movq	%rax, 24(%rsi)
.L136:
	movsbl	(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
.L135:
	movsbl	(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
.L134:
	movsbl	(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
.L133:
	movsbl	(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
.L132:
	movsbl	(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
.L131:
	movsbl	(%rdi,%rdx), %eax
	movl	%edx, %r9d
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	addq	$1, %rdx
	cmpq	%r11, %rdx
	je	.L166
.L4:
	movsbl	(%rdi,%rdx), %eax
	leaq	1(%rdx), %rcx
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	movsbl	1(%rdi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rcx,8)
	movsbl	2(%rdi,%rdx), %eax
	addq	$2, %rdx
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	movsbl	2(%rdi,%rcx), %eax
	leaq	6(%rcx), %rdx
	movl	%edx, %r9d
	subl	$96, %eax
	cltq
	movq	%rax, 16(%rsi,%rcx,8)
	movsbl	3(%rdi,%rcx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, 24(%rsi,%rcx,8)
	movsbl	4(%rdi,%rcx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, 32(%rsi,%rcx,8)
	movsbl	5(%rdi,%rcx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, 40(%rsi,%rcx,8)
	movsbl	6(%rdi,%rcx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rsi,%rdx,8)
	leaq	7(%rcx), %rdx
	cmpq	%r11, %rdx
	jne	.L4
.L166:
	cmpl	%r10d, %r8d
	je	.L177
	movl	%r8d, %ebp
	leal	-1(%r8), %ebx
	movl	%r10d, %eax
	subl	%r10d, %ebp
	leaq	s(%rip), %rsi
	leaq	in(%rip), %rcx
	leal	-16(%rbp), %r11d
	movl	%ebx, %edx
	subl	%r10d, %edx
	shrl	$4, %r11d
	addl	$1, %r11d
	movl	%r11d, %r12d
	sall	$4, %r12d
	cmpl	$14, %edx
	jbe	.L6
	leaq	s(%rip), %rsi
	addq	$1, %rax
	leaq	in(%rip), %rcx
	vmovdqa	.LC0(%rip), %xmm3
	leal	-1(%r11), %edx
	leaq	(%rsi,%rax), %rdi
	leaq	(%rcx,%rax,8), %rax
	movl	$1, %r10d
	andl	$1, %edx
	vmovdqa	(%rdi), %xmm0
	subq	$-128, %rax
	addq	$16, %rdi
	vpmovsxbw	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxbw	%xmm0, %xmm0
	vpmovsxwd	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpmovsxwd	%xmm1, %xmm1
	vpmovsxwd	%xmm0, %xmm2
	vpsrldq	$8, %xmm0, %xmm0
	vpaddd	%xmm3, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm5
	vpsrldq	$8, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm4
	vpaddd	%xmm3, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm2, %xmm2
	vpmovsxwd	%xmm0, %xmm0
	vmovaps	%xmm4, -112(%rax)
	vpmovsxdq	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm0, %xmm0
	vpmovsxdq	%xmm1, %xmm1
	vmovaps	%xmm5, -128(%rax)
	vmovaps	%xmm1, -80(%rax)
	vpmovsxdq	%xmm2, %xmm1
	vpsrldq	$8, %xmm2, %xmm2
	vpmovsxdq	%xmm2, %xmm2
	vmovaps	%xmm1, -64(%rax)
	vpmovsxdq	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxdq	%xmm0, %xmm0
	vmovaps	%xmm4, -96(%rax)
	vmovaps	%xmm2, -48(%rax)
	vmovaps	%xmm1, -32(%rax)
	vmovaps	%xmm0, -16(%rax)
	cmpl	$1, %r11d
	jbe	.L7
	testl	%edx, %edx
	je	.L8
	vmovdqa	(%rdi), %xmm0
	subq	$-128, %rax
	addq	$16, %rdi
	movl	$2, %r10d
	vpmovsxbw	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxbw	%xmm0, %xmm0
	vpmovsxwd	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpmovsxwd	%xmm1, %xmm1
	vpmovsxwd	%xmm0, %xmm2
	vpsrldq	$8, %xmm0, %xmm0
	vpaddd	%xmm3, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm5
	vpsrldq	$8, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm4
	vpaddd	%xmm3, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm2, %xmm2
	vpmovsxwd	%xmm0, %xmm0
	vmovaps	%xmm4, -112(%rax)
	vpmovsxdq	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm0, %xmm0
	vpmovsxdq	%xmm1, %xmm1
	vmovaps	%xmm5, -128(%rax)
	vmovaps	%xmm1, -80(%rax)
	vpmovsxdq	%xmm2, %xmm1
	vpsrldq	$8, %xmm2, %xmm2
	vpmovsxdq	%xmm2, %xmm2
	vmovaps	%xmm1, -64(%rax)
	vpmovsxdq	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxdq	%xmm0, %xmm0
	vmovaps	%xmm4, -96(%rax)
	vmovaps	%xmm2, -48(%rax)
	vmovaps	%xmm1, -32(%rax)
	vmovaps	%xmm0, -16(%rax)
	cmpl	$2, %r11d
	jbe	.L7
	.p2align 4,,10
	.p2align 3
.L8:
	addl	$2, %r10d
	addq	$32, %rdi
	addq	$256, %rax
	vmovdqa	-32(%rdi), %xmm0
	vpmovsxbw	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxbw	%xmm0, %xmm0
	vpmovsxwd	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpmovsxwd	%xmm1, %xmm1
	vpmovsxwd	%xmm0, %xmm2
	vpsrldq	$8, %xmm0, %xmm0
	vpaddd	%xmm3, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm5
	vpsrldq	$8, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm4
	vpaddd	%xmm3, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm2, %xmm2
	vpmovsxwd	%xmm0, %xmm0
	vmovaps	%xmm4, -240(%rax)
	vpmovsxdq	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm0, %xmm0
	vpmovsxdq	%xmm1, %xmm1
	vmovaps	%xmm5, -256(%rax)
	vmovaps	%xmm1, -208(%rax)
	vpmovsxdq	%xmm2, %xmm1
	vpsrldq	$8, %xmm2, %xmm2
	vpmovsxdq	%xmm2, %xmm2
	vmovaps	%xmm1, -192(%rax)
	vpmovsxdq	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxdq	%xmm0, %xmm0
	vmovaps	%xmm4, -224(%rax)
	vmovaps	%xmm2, -176(%rax)
	vmovaps	%xmm1, -160(%rax)
	vmovaps	%xmm0, -144(%rax)
	vmovdqa	-16(%rdi), %xmm0
	vpmovsxbw	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxbw	%xmm0, %xmm0
	vpmovsxwd	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpmovsxwd	%xmm1, %xmm1
	vpmovsxwd	%xmm0, %xmm2
	vpsrldq	$8, %xmm0, %xmm0
	vpaddd	%xmm3, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm5
	vpsrldq	$8, %xmm4, %xmm4
	vpmovsxdq	%xmm4, %xmm4
	vpaddd	%xmm3, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm2, %xmm2
	vpmovsxwd	%xmm0, %xmm0
	vmovaps	%xmm4, -112(%rax)
	vpmovsxdq	%xmm1, %xmm4
	vpsrldq	$8, %xmm1, %xmm1
	vpaddd	%xmm3, %xmm0, %xmm0
	vpmovsxdq	%xmm1, %xmm1
	vmovaps	%xmm5, -128(%rax)
	vmovaps	%xmm1, -80(%rax)
	vpmovsxdq	%xmm2, %xmm1
	vpsrldq	$8, %xmm2, %xmm2
	vpmovsxdq	%xmm2, %xmm2
	vmovaps	%xmm1, -64(%rax)
	vpmovsxdq	%xmm0, %xmm1
	vpsrldq	$8, %xmm0, %xmm0
	vpmovsxdq	%xmm0, %xmm0
	vmovaps	%xmm4, -96(%rax)
	vmovaps	%xmm2, -48(%rax)
	vmovaps	%xmm1, -32(%rax)
	vmovaps	%xmm0, -16(%rax)
	cmpl	%r10d, %r11d
	ja	.L8
.L7:
	addl	%r12d, %r9d
	cmpl	%ebp, %r12d
	je	.L5
.L6:
	movslq	%r9d, %rdx
	movsbl	(%rsi,%rdx), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rcx,%rdx,8)
	leal	1(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	2(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	3(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	4(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	5(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	6(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	7(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	8(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	9(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	10(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	11(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	12(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	leal	13(%r9), %eax
	cmpl	%eax, %r8d
	jl	.L5
	cltq
	addl	$14, %r9d
	movsbl	(%rsi,%rax), %edx
	subl	$96, %edx
	cmpl	%r9d, %r8d
	movslq	%edx, %rdx
	movq	%rdx, (%rcx,%rax,8)
	jl	.L5
	movslq	%r9d, %r9
	movsbl	(%rsi,%r9), %eax
	subl	$96, %eax
	cltq
	movq	%rax, (%rcx,%r9,8)
.L5:
	imulq	$233, hsh1(%rip), %rax
	movl	%ebx, %esi
	movl	$16, %edx
	leaq	hsh1(%rip), %rdi
	leaq	16(,%rsi,8), %r9
	andl	$7, %esi
	addq	8+in(%rip), %rax
	cmpq	%r9, %rdx
	movq	%rax, 8+hsh1(%rip)
	je	.L13
	testq	%rsi, %rsi
	je	.L14
	cmpq	$1, %rsi
	je	.L125
	cmpq	$2, %rsi
	je	.L126
	cmpq	$3, %rsi
	je	.L127
	cmpq	$4, %rsi
	je	.L128
	cmpq	$5, %rsi
	je	.L129
	cmpq	$6, %rsi
	je	.L130
	imulq	$233, %rax, %rax
	movl	$24, %edx
	addq	16+in(%rip), %rax
	movq	%rax, 16+hsh1(%rip)
.L130:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
.L129:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
.L128:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
.L127:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
.L126:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
.L125:
	imulq	$233, %rax, %rax
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	addq	$8, %rdx
	cmpq	%r9, %rdx
	je	.L13
	.p2align 4,,10
	.p2align 3
.L14:
	imulq	$233, %rax, %rax
	leaq	8(%rdx), %rsi
	addq	(%rcx,%rdx), %rax
	movq	%rax, (%rdi,%rdx)
	imulq	$233, %rax, %rax
	addq	8(%rcx,%rdx), %rax
	movq	%rax, 8(%rdi,%rdx)
	imulq	$233, %rax, %rax
	addq	16(%rcx,%rdx), %rax
	movq	%rax, 16(%rdi,%rdx)
	leaq	56(%rsi), %rdx
	imulq	$233, %rax, %rax
	addq	16(%rcx,%rsi), %rax
	movq	%rax, 16(%rdi,%rsi)
	imulq	$233, %rax, %rax
	addq	24(%rcx,%rsi), %rax
	movq	%rax, 24(%rdi,%rsi)
	imulq	$233, %rax, %rax
	addq	32(%rcx,%rsi), %rax
	movq	%rax, 32(%rdi,%rsi)
	imulq	$233, %rax, %rax
	addq	40(%rcx,%rsi), %rax
	movq	%rax, 40(%rdi,%rsi)
	imulq	$233, %rax, %rax
	addq	48(%rcx,%rsi), %rax
	cmpq	%r9, %rdx
	movq	%rax, 48(%rdi,%rsi)
	jne	.L14
.L13:
	leaq	hsh2(%rip), %r10
	movslq	%r8d, %rsi
	movq	%rbx, %r11
	salq	$3, %rsi
	notq	%r11
	movq	$-8, %rdx
	imulq	$233, 8(%r10,%rsi), %rax
	salq	$3, %r11
	movq	%r11, %rdi
	negq	%rdi
	addq	(%rcx,%rsi), %rax
	subq	$8, %rdi
	shrq	$3, %rdi
	andl	$7, %edi
	cmpq	%r11, %rdx
	movq	%rax, (%r10,%rsi)
	je	.L171
	testq	%rdi, %rdi
	je	.L12
	cmpq	$1, %rdi
	je	.L119
	cmpq	$2, %rdi
	je	.L120
	cmpq	$3, %rdi
	je	.L121
	cmpq	$4, %rdi
	je	.L122
	cmpq	$5, %rdi
	je	.L123
	cmpq	$6, %rdi
	je	.L124
	leaq	(%rcx,%rdx), %rdi
	movq	$-16, %rdx
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	-8+hsh2(%rip), %rdi
	movq	%rax, (%rdi,%rsi)
.L124:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	movq	%rax, (%rdi,%rsi)
.L123:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	movq	%rax, (%rdi,%rsi)
.L122:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	movq	%rax, (%rdi,%rsi)
.L121:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	movq	%rax, (%rdi,%rsi)
.L120:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	movq	%rax, (%rdi,%rsi)
.L119:
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$8, %rdx
	cmpq	%r11, %rdx
	movq	%rax, (%rdi,%rsi)
	je	.L171
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	(%rcx,%rdx), %rdi
	leaq	-8(%rdx), %r9
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	subq	$16, %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%r9), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%r9), %rdi
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-16(%r9), %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-24(%r9), %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-32(%r9), %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-40(%r9), %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-48(%r9), %rdx
	movq	%rax, (%rdi,%rsi)
	leaq	(%rcx,%rdx), %rdi
	imulq	$233, %rax, %rax
	addq	(%rdi,%rsi), %rax
	leaq	(%r10,%rdx), %rdi
	leaq	-56(%r9), %rdx
	cmpq	%r11, %rdx
	movq	%rax, (%rdi,%rsi)
	jne	.L12
.L171:
	testl	%r8d, %r8d
	movq	$1, pows(%rip)
	jle	.L174
	leaq	pows(%rip), %rax
	leaq	16+pows(%rip), %rdx
	movq	$233, 8+pows(%rip)
	leaq	16(%rax,%rbx,8), %rsi
	leaq	16+pows(%rip), %rax
	movq	%rsi, %rcx
	subq	%rax, %rcx
	movl	$233, %eax
	shrq	$3, %rcx
	andl	$7, %ecx
	cmpq	%rsi, %rdx
	je	.L174
	testq	%rcx, %rcx
	je	.L16
	cmpq	$1, %rcx
	je	.L113
	cmpq	$2, %rcx
	je	.L114
	cmpq	$3, %rcx
	je	.L115
	cmpq	$4, %rcx
	je	.L116
	cmpq	$5, %rcx
	je	.L117
	cmpq	$6, %rcx
	je	.L118
	movq	$54289, (%rdx)
	leaq	24+pows(%rip), %rdx
	movl	$54289, %eax
.L118:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
.L117:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
.L116:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
.L115:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
.L114:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
.L113:
	imulq	$233, %rax, %rax
	addq	$8, %rdx
	movq	%rax, -8(%rdx)
	cmpq	%rsi, %rdx
	je	.L174
	.p2align 4,,10
	.p2align 3
.L16:
	imulq	$233, %rax, %rax
	addq	$64, %rdx
	movq	%rax, -64(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -56(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -48(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -40(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -32(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -24(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -16(%rdx)
	imulq	$233, %rax, %rax
	movq	%rax, -8(%rdx)
	cmpq	%rsi, %rdx
	jne	.L16
.L174:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L177:
	.cfi_restore_state
	leal	-1(%r8), %ebx
	leaq	in(%rip), %rcx
	jmp	.L5
.L2:
	jne	.L178
	movq	$1, pows(%rip)
	jmp	.L174
.L178:
	leal	-1(%r8), %ebx
	leaq	in(%rip), %rcx
	jmp	.L13
	.cfi_endproc
.LFE0:
	.size	_Z7inithshv, .-_Z7inithshv
	.p2align 4,,15
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
	.p2align 4,,15
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
	.p2align 4,,15
	.type	_Z6merge1iiii, @function
_Z6merge1iiii:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%ecx, %r10d
	movl	%edx, %r9d
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	_Z8segment1ii
	movl	%r10d, %esi
	leaq	pows(%rip), %rdx
	movl	%r9d, %edi
	subl	%r9d, %esi
	addl	$1, %esi
	movslq	%esi, %rsi
	imulq	(%rdx,%rsi,8), %rax
	movl	%r10d, %esi
	movq	%rax, %r8
	call	_Z8segment1ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	addq	%r8, %rax
	ret
	.cfi_endproc
.LFE3:
	.size	_Z6merge1iiii, .-_Z6merge1iiii
	.p2align 4,,15
	.type	_Z6merge2iiii, @function
_Z6merge2iiii:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%edi, %r10d
	movl	%esi, %r11d
	movl	%edx, %edi
	movl	%ecx, %esi
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	_Z8segment2ii
	movl	%r11d, %edx
	leaq	pows(%rip), %rcx
	movl	%r11d, %esi
	subl	%r10d, %edx
	movl	%r10d, %edi
	addl	$1, %edx
	movslq	%edx, %rdx
	imulq	(%rcx,%rdx,8), %rax
	movq	%rax, %r9
	call	_Z8segment2ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	addq	%r9, %rax
	ret
	.cfi_endproc
.LFE4:
	.size	_Z6merge2iiii, .-_Z6merge2iiii
	.p2align 4,,15
	.type	_Z5judgeiiii, @function
_Z5judgeiiii:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%edi, %r11d
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movl	%edx, %r12d
	movl	%esi, %ebx
	movl	%ecx, %r13d
	call	_Z6merge1iiii
	movl	%r13d, %ecx
	movq	%rax, %r14
	movl	%r12d, %edx
	movl	%ebx, %esi
	movl	%r11d, %edi
	call	_Z6merge2iiii
	cmpq	%rax, %r14
	popq	%rbx
	sete	%al
	popq	%r12
	popq	%r13
	popq	%r14
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
	subq	$40, %rsp
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
	movl	%eax, -64(%rbp)
	jle	.L191
	addl	$1, %eax
	movl	$1, -52(%rbp)
	movl	%eax, -60(%rbp)
.L197:
	movl	-52(%rbp), %r13d
	.p2align 4,,10
	.p2align 3
.L196:
	movl	%r13d, %eax
	subl	-52(%rbp), %eax
	movl	$1, %ebx
	movl	%eax, -68(%rbp)
	.p2align 4,,10
	.p2align 3
.L195:
	cmpl	-64(%rbp), %ebx
	jg	.L192
	movl	-68(%rbp), %eax
	movl	%ebx, %r15d
	movl	-52(%rbp), %edi
	notl	%r15d
	addl	-60(%rbp), %r15d
	movl	%ebx, %ecx
	movl	%ebx, %edx
	movl	%r13d, %esi
	subl	%ebx, %eax
	addl	$2, %eax
	movl	%eax, -56(%rbp)
	andl	$3, %r15d
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L204
	movl	-56(%rbp), %eax
	addl	%ebx, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L204:
	leal	1(%rbx), %r14d
	cmpl	-60(%rbp), %r14d
	je	.L192
	testl	%r15d, %r15d
	je	.L194
	cmpl	$1, %r15d
	je	.L222
	cmpl	$2, %r15d
	je	.L223
	movl	-52(%rbp), %edi
	movl	%r14d, %ecx
	movl	%ebx, %edx
	movl	%r13d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L206
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L206:
	addl	$1, %r14d
.L223:
	movl	-52(%rbp), %edi
	movl	%r14d, %ecx
	movl	%ebx, %edx
	movl	%r13d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L209
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L209:
	addl	$1, %r14d
.L222:
	movl	-52(%rbp), %edi
	movl	%r14d, %ecx
	movl	%ebx, %edx
	movl	%r13d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L212
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L212:
	addl	$1, %r14d
	cmpl	-60(%rbp), %r14d
	je	.L192
.L194:
	movl	-52(%rbp), %edi
	movl	%r14d, %ecx
	movl	%ebx, %edx
	movl	%r13d, %esi
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L193
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L193:
	leal	1(%r14), %r15d
	movl	-52(%rbp), %edi
	movl	%ebx, %edx
	movl	%r13d, %esi
	movl	%r15d, %ecx
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L215
	movl	-56(%rbp), %eax
	addl	%r15d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L215:
	leal	1(%r15), %r14d
	movl	-52(%rbp), %edi
	movl	%ebx, %edx
	movl	%r13d, %esi
	movl	%r14d, %ecx
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L217
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L217:
	leal	2(%r15), %r14d
	movl	-52(%rbp), %edi
	movl	%ebx, %edx
	movl	%r13d, %esi
	movl	%r14d, %ecx
	call	_Z5judgeiiii
	testb	%al, %al
	je	.L219
	movl	-56(%rbp), %eax
	addl	%r14d, %eax
	cltq
	addq	%rax, %r12
	movq	%r12, ans(%rip)
.L219:
	leal	3(%r15), %r14d
	cmpl	-60(%rbp), %r14d
	jne	.L194
.L192:
	addl	$1, %ebx
	cmpl	-60(%rbp), %ebx
	jne	.L195
	addl	$1, %r13d
	cmpl	%r13d, -64(%rbp)
	jge	.L196
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
	cmpl	%eax, -60(%rbp)
	movq	%r12, ans(%rip)
	jne	.L197
.L191:
	leaq	.LC2(%rip), %rdi
	movq	%r12, %rsi
	xorl	%eax, %eax
	call	printf@PLT
	addq	$40, %rsp
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
