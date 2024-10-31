
        .global main
        .func main

main:
        
    PUSH {LR}
	vmov.f32	s0,#0.125		@Assigning radius via immediate value
	vmul.f32 	s0, s0, s0		@s0 = r^2
	ldr	r2,=piNumber			@loading pinumber into r2
	
	vldr		s1, [r2]		@s1 = value pointed to by r2
	vmul.f32	s0, s0, s1		@s0 = pi * r^2
	vcvt.f64.f32 d0, s0			@stored result into d0
	
	ldr r0, =area				@loading print statement
	vmov r1, r2, d0				@floats print using double precision, 
	bl printf					@moving d0 into r1 and r2 to get an accurate number
	
_exit:
        POP {PC}
        MOV PC, LR

piNumber: .float 3.141593

.data
area: .asciz "Area = %f\n"		@print statement
