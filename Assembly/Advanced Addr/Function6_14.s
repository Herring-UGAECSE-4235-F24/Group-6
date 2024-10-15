@ **NOTE: THIS IS A GROUP ASSEMBLY ASSIGNMENT**

@this code calculates x^2 + 2x + 3 with "x" stored in r9 which you will need to add to the program.  
@Deliverable 1: What is the range of valid values for r9?
@Deliverable 2: Show your code written with R9 added so that it runs with "x = 3".
@Deliverable 3: How many clocks does this take to execute?
@Deliverable 4: Rewrite the function without using a lookup table. Show your code working with "x = 3".  How many clocks to run?
@Deliverable 5: What are pros and cons of the two methods: 1) Look-up table, 2) Mathematical function.


@Deliverable 6: Now write a program with a look-up table that takes a degree value from 0-90 (including 0 and 90) in multiples of 4 (0, 4, 8, 12, etc...) and stores into R9 from the keyboard input.
@ The program will use the degree value and return the sin x 1000 in R0 and the cosine x 1000 in R1 (so this is to 3 decimal places).  For example if R9 = 32, R0 would have 530 and r1 would have 848.  
@ Display the result on the terminal in decimal correctly and with the following format using the example with 32 as the angle...
@ Cosine of 32 = 0.530 and Sine of 32 = 0.848
@ Show your code in your writeup.
@ Code steps: 1) Ask for input "Enter Angle:", 2) If not within range, do nothing, 3) If within range, display the output result and go back to 1) for new input.
@ Deliverable 7: I will check results in class.


	.global main
	.func main
main:
	PUSH {LR}
	adr	r8, cosine		@ point to lookup tables
	adr	r9, sine
	
	ldr r0, =int	@formatting scanf to take an int
	ldr r1, =input
	bl scanf
	
	ldr r1, =input
	ldr r10, [r1]
	ldr r1, [r1]	@user input stored in r1 and r10
	
	cmp r1, #0		@if input is < 0 or > 90, exit
	blt exit
	cmp r1, #90
	bgt exit
	
	mov r7, #4
	udiv r5, r1, r7		@r5 = r1/4
	mul r6, r5, r7		@r6 = r5 * 4
	sub r1, r1, r6		@r1= remainder
	cmp r1, #0
	bne exit
	
	ldr r4, [r9, r10]		@sine value
	ldr r3, r10				@printing input
	ldr r2, [r8, r10]		@cosine value
	ldr r1, r10				@printing input again
	ldr r0, =output			@formatting print
	bl printf
	
	
exit:	
	POP {PC}
    MOV PC, LR
   
cosine: .word	1000, 998, 990, 978, 961, 940, 914, 883, 848, 809, 766, 719, 669, 616, 559, 500, 438, 375, 309, 242, 174, 105, 35, 0
sine: .word 	0, 70, 139, 208, 276, 342, 407, 469, 530, 588, 643, 695, 743, 788, 829, 866, 899, 927, 951, 970, 985, 995, 999, 1000

.data
int: .asciz "%d"
@test: .asciz "Cosine of %d and Sine of %d\n"
output: .asciz "Cosine of %d = 0.%03d and Sine of %d = 0.%03d"
input: .byte 0
