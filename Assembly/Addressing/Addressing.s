@ Deliverable 1:  Describe the function of the program.
@ Now, let's investigate what you can and can't do on the instructions.
@ Deliverable 2: Can you replace each [Rx] with the value?  For example replace [R6] with [0x90]?
@ Deliverable 3: Try it for each instance for LDR and STR.  Results?
@ Deliverable 4: Can you explain what needs to be added to the original program to make it run without issues?

	.text
	.global _start

_start:	
	LDR R6,=value1		@R6 = value1
	LDR R1, [R6]	 	@R1 = [R6], or the value at value1. 1 in this case
  	LDR R6,=value2	 	@R6 = value2
  	LDR R2,[R6]	  	@R1 = [R6], 2 in this case
  	ADD R2,R2,R1	  	@R2 = R2 + R1
  	LDR R6,=value3	  	@R6 = value3
 	STR R2,[R6]	  	@[value3] = R2, 3 in this case
		
	mov   	r7, #1
	svc  	0

.data
value1:	.word 1		@first number being added
value2: .word 2		@second number being added
value3: .word 0		@the sum. given an arbitrary starting value
