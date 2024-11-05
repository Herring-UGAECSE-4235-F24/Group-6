	.global main
        .func main

main:
	PUSH {LR}
	ldr r0, =startup	@Printing the initial welcome message
	bl printf
	
	ldr r0, =float		@Setting up the input for x
	ldr r1, =input
	bl scanf
	
	ldr r0, =input		@Converting to a double to ensure printing
	vldr s0, [r0]
	vcvt.f64.f32 d0, s0
	vmov r1, r2, d0
	ldr r0, =print		@Printing X
	bl printf
	ldr r0, =input		@Setting s0 to X
	vldr s0, [r0]
	vmov.f32 s4, #1.0	@Intializing registers
	vmov.f32 s1, #1.0
	
	vcmp.f32 s0, s4		@Checking for zero factorial
	vmrs apsr_nzcv, fpscr 	@Moving updated arm flags to fpscr
	blt printing		@If n < 1, print
fact:
	vmul.f32 s3,s0,s1 	@Multiplying the the base by the current iteration
	vmov.f32 s1, s3 	@Moving answer to the register that will be multiplied 
	vcmp.f32 s0, s4 	@Updating the flags
	vsub.f32 s0, s0, s4 	@Subtracting one for the next iteration
	vmrs apsr_nzcv, fpscr 	@Updating flags
	bne fact

printing:	
	vcvt.f64.f32 d0, s1	@Converting to double for printing
	ldr r0, =output
	vmov r1, r2, d0
	bl printf

_exit:
        POP {PC}
        MOV PC, LR
	
	@HIGHEST ACCURATE NUMBER = 13
	
.data
startup: .asciz "Calculate n!. Enter n: "	@Welcome message
output: .asciz "! = %f\n"
input:	.word 0					@Input is stored here
float:  .asciz "%f"				@Printing in pieces to avoid using the stack
print:  .asciz "%.0f"				@truncating float when printing
