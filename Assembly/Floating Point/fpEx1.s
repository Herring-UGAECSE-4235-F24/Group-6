
        .global main
        .func main

main:
        
    PUSH {LR}
	vmov.f32	s0,#0.125
	vmul.f32 	s0, s0, s0
	ldr	r2,=piNumber
	vldr		s1, [r2]
	vmul.f32	s0, s0, s1
	
	ldr r0, =area
	ldr r1, [r2]
	bl printf
	
_exit:
        POP {PC}
        MOV PC, LR

piNumber: .float 3.141593

.data
area: .asciz "Area = %f\n"
