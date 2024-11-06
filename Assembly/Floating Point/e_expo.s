	.global e_expo
    .func e_expo

	@THIS VERSION OF EXPO SHOULD BE LINKED WITH etothex.c
e_expo:
	PUSH {LR}
	
	mov r4, r0
	
	vmov.f32 s1, #1.0	@initializing result
	cmp r4, #0			@checking for zero exponent
	beq _exit		@if so, exit
expo:
	vmul.f32 s3,s1,s0	@multiply by x
	vmov.f32 s1, s3		@update result
	subs r4, #1			@decrement exponent as a counter
	bne expo			@if exponent isn't 0, multiply again
	

_exit:
		vmov.f32 s0, s1		@moving result to s0 to access from C file
        POP {PC}			@printing the result is not needed
        BX LR
		
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
