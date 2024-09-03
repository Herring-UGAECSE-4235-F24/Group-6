@ Deliverable 1:  Describe the function of the program.
@ Now, let's investigate what you can and can't do on the instructions.
@ Deliverable 2: Can you replace each [Rx] with the value?  For example replace [R6] with [0x90]?
@ Deliverable 3: Try it for each instance for LDR and STR.  Results?
@ Deliverable 4: Can you explain what needs to be added to the original program to make it run without issues?

	.text
	.global _start

_start:	
	LDR R6,=0x90		@R6 = 0x90
	LDR R1, [R6]	 	@R1 = [0x90]
  	@LDR R6,=0x94	 	@R6 = 0x94
  	@LDR R2,[R6]	  	@R1 = [0x94]
  	@ADD R2,R2,R1	  	@R2 = R2 + R1
  	@LDR R6,=0x300	  	@R6 = 0x300
 	@STR R2,[R6]	  	@[0x300] = R2
		
	mov   	r7, #1
	svc  	0
