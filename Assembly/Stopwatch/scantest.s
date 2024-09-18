


		.global main
		.func main
main:
		PUSH {LR}
		LDR R0, =format
		LDR R1, =input
		BL scanf
		
		LDRB R2, =compare
		@LDRB R3, =compare
		@LDRB R3, [R1]
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
		.byte 0
compare:
		.byte 'c'
equal:
		.asciz "c was pressed"
compare2:
		.byte 'c'
	
