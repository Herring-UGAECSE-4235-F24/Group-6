	.global e_factorial
        .func e_factorial

	@THIS VERSION OF FACTORIAL SHOULD BE LINKED WITH e_expo.c
e_factorial:
	PUSH {LR}
	vmov.f32 s4, #1.0	@Intializing registers
	vmov.f32 s1, #1.0
	
	vcmp.f32 s0, s4		@Checking for zero factorial
	vmrs apsr_nzcv, fpscr 	@Moving updated arm flags to fpscr
	blt _exit		@If n < 1, exit
fact:
	vmul.f32 s3,s0,s1 	@Multiplying the the base by the current iteration
	vmov.f32 s1, s3 	@Moving answer to the register that will be multiplied 
	vcmp.f32 s0, s4 	@Updating the flags
	vsub.f32 s0, s0, s4 	@Subtracting one for the next iteration
	vmrs apsr_nzcv, fpscr 	@Updating flags
	bne fact

_exit:
		vmov.f32 s0, s1		@moving result to s0 to access from C file
        POP {PC}			@printing the result is not needed
        BX LR
	
	@HIGHEST ACCURATE NUMBER = 13
	
.data
startup: .asciz "Calculate n!. Enter n: "	@Welcome message
output: .asciz "! = %f\n"
input:	.word 0					@Input is stored here
float:  .asciz "%f"				@Printing in pieces to avoid using the stack
print:  .asciz "%.0f"				@truncating float when printing
