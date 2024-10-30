

	.global main
    .func main
    
main: @@ set runfast mode and rounding to nearest
	
	PUSH {LR}
	ldr r0, =float
	ldr r1, =input
	bl scanf
	
	ldr r0, =input
	vldr s0, [r0]
	
	@vmov s0, #0.125
	vmrs r1, fpscr @ get FPSCR contents in r1
	bic r2, r1, #(0b1111<<23)
	orr r2, r2, #(0b1100<<23)
	vmsr fpscr, r2 @ store settings in FPSCR
	vmul.f32 s1,s0,s0 @ s1 = x^2
	ldr r0,=ctab @ get address of coefficients
	vldmia r0!,{s16-s20} @ load all coefficients into Bank 2
	vmul.f32 s8,s0,s1 @ s8 = x^3
	vmul.f32 s9,s8,s1 @ s9 = x^5
	vmul.f32 s10,s9,s1 @ s10 = x^7
	vmul.f32 s11,s10,s1 @ s11 = x^9
	vmul.f32 s12,s11,s1 @ s12 = x^11
	@@ Set VFP for vector mode
	bic r2, r2, #(0b11111<<16) @ set rounding, stride to 1,
	orr r2, r2, #(0b00100<<16) @ and vector length to 5
	vmsr fpscr, r2 @ store settings in FPSCR
	vmul.f32 s24,s8,s16 @ VECTOR operation x^(2n+1) * coeff[n]
	vmsr fpscr, r1 @ restore original FPSCR
	@@ Add terms in Bank 3 to the result in s0
	vadd.f32 s24,s24,s25
	vadd.f32 s26,s26,s27
	vadd.f32 s0,s0,s24
	vadd.f32 s26,s26,s28
	vadd.f32 s0,s0,s26
	
	
	vcvt.f64.f32 d0, s0
	ldr r0, =output
	vmov r1, r2, d0
	bl printf
_exit:
        POP {PC}
        MOV PC, LR
        
.data
	ctab: .word 0xBE2AAAAB @ -1.666667e-01
	.word 0x3C088889 @ 8.333334e-03
	.word 0xB9500D01 @ -1.984127e-04
	.word 0x3638EF1D @ 2.755732e-06
	.word 0xB2D7322B @ -2.505211e-08
	input:
		.word 0
	output:
		.asciz "Result = %f\n"
	float:
		.asciz "%f"
