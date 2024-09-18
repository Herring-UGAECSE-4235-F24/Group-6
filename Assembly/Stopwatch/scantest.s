
		.global main
		.func main
main:
		PUSH {LR}
		LDR R0, =0
		BL E4235_KYBdeblock
		
		BL read
		
read:
		LDR R0, =input
		LDRB R4, [R0]
		LDRB R5, [R0]
		
loop:	LDR R0, =format
		LDR R1, =input
		BL scanf
		
		LDR R0, =input
		LDRB R5, [R0]
		CMP R4, R5
		
		LDR R0, =test
		BL printf
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
        POP {PC}
        MOV PC, LR
        
.data
format:
		.asciz "%c"
input:
		.byte 'c'
compare:
		.byte 'c'
equal:
		.asciz "c was pressed\n"
test:
		.asciz "looping\n"
null:
		.byte '\0'
	
