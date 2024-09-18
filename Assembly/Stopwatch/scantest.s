
		.global main
		.func main
main:
		PUSH {LR}
		LDR R0, =1
		BL E4235_KYBdeblock
		
		BL read

read:
		LDR R0, =input
		LDRB R4, [R0]
		LDRB R5, [R0]
  		LDR R6, =0
		
loop:		LDR R0, =char
		LDR R1, =input
		BL scanf
		
		LDR R0, =input
		LDRB R5, [R0]
		CMP R4, R5
  		ADD R6, R6, #1
    
		BEQ loop
		BNE check
		
check:	
		LDR R0, =input
		LDRB R3, [R0]
		LDR R0, =compare
		LDRB R2, [R0]
		
		CMP R2, R3
		BNE _exit
		LDR R0, =equal
		BL printf
		
_exit:
		LDR R0, =int
	 	MOV R1, R6
   		BL printf
	        POP {PC}
	        MOV PC, LR
        
.data
char:
		.asciz "%c"
input:
		.byte 0
compare:
		.byte 'c'
equal:
		.asciz "c was pressed\n"
int:
		.asciz "%d\n"
null:
		.byte '\0'
	
