	.global main
    .func main

main:
	PUSH {LR}
	ldr r0, =enterx		@enter x message
	bl printf
	ldr r0, =float		@reading x from user
	ldr r1, =input
	bl scanf

	ldr r0, =entern		@enter n message
	bl printf
	ldr r0, =expinput	@reading x from user
	ldr r1, =expplace
	bl scanf
	
	ldr r0, =input		@converting x to double and printing
	vldr s0, [r0]
	vcvt.f64.f32 d0, s0	
	vmov r1, r2, d0
	ldr r0, =print
	bl printf

	ldr r0, =expplace	@printing n
	ldr r1, [r0]
	ldr r0, =exp
	bl printf
	
	ldr r0, =input	@storing x and n into their respective registers
	vldr s0, [r0]
	ldr r1, =expplace
	ldr r4, [r1]
	
	vmov.f32 s1, #1.0	@initializing result
expo:
	vmul.f32 s3,s1,s0	@multiply n by result
	vmov.f32 s1, s3		@update result
	subs r4, #1			@decrement exponent as a counter
	bne expo			@if exponent isn't 0, multiply again
	
	vcvt.f64.f32 d0, s1	@convert to double and print
	ldr r0, =output
	vmov r1, r2, d0
	bl printf

_exit:
        POP {PC}
        MOV PC, LR
		
.data
input:	.word 0								@storing x
expplace: .word 0							@storing n
enterx: .asciz "Calculate x^n. Enter x: "	@startup message
entern: .asciz "Enter n: "					@enter n message
output: .asciz " = %f\n"					@printing in pieces to avoid using stack
exp: .asciz "^%d"							
expinput: .asciz "%d"						@reading in an int
float:  .asciz "%f"							@reading in a float
print:  .asciz "%.0f"						@truncating float when printing
