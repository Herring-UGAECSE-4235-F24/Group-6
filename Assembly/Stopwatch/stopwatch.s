@This is a delay program for 4230.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:000, the stopwatch should go back to 0:00:00 and keep running.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.

	.global main
	.func main
main:
	PUSH {LR}
	LDR R0, =1
	BL E4235_KYBdeblock
	BL clear
	
run:
	LDR R0, =test	
	BL printf
	
run_loop:		@needs to keep incrementing and printing until 'l' 's' or 'c' are pressed
	LDR R0, =char
	LDR R1, =input
	BL scanf
	
	LDR R0, =input	@storing input
	LDRB R4, [R0]
	
	LDR R0, =lap_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'l'
	BEQ lap
	
	LDR R0, =stop_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 's'
	BEQ stop
	
	LDR R0, =clr_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'c'
	BEQ clear	@resets to 0:0:0
	BNE run_loop

clear:
	LDR R7, =#0	@ hundrendths
	LDR R8, =#0	@ seconds
	LDR R9, =#0	@ minutes
	BL _print

clr_loop:
	LDR R0, =char
	LDR R1, =input
	BL scanf
	
	LDR R0, =input	@storing input
	LDRB R4, [R0]
	
	LDR R0, =run_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'r'
	
	BEQ run		@if so, run the clock starting from 0:0:0
	BNE clr_loop	@if not, keep scanning
	
	
_print:
	PUSH {LR}		@saving LR
	
        LDR R0, =time		@formatting printf        
        MOV R3, R7
	MOV R2, R8
	MOV R1, R9
        BL printf		
	
	POP {LR}		@LR has been changed by BL printf. restoring it
	BX LR

_inc:
	ADD R7, R7, #1		@increment hundrenths
	CMP R7, #100		
	BEQ _hunds
	BNE _loop		@runs loop until a second passes
	
_hunds:	
	SUBS R7, R7, #100	@resetting hundreths
	ADD R8, R8, #1		@increment seconds
	CMP R8, #60
	BEQ _secs
	BNE _loop		@runs loop until a minute passes
_secs:
	SUBS R8, R8, #60	@resets seconds
	ADD R9, R9, #1		@increment minutes
	CMP R9, #2
	BEQ _done
	BNE _loop		@runs until 2 mins pass
_done:
        SUBS R9, R9, #2		@resets minutes
	B _loop
	
_loop:	
		LDR R3, =8826100/2	@ r3 = number of instructions for .01 seconds
_inner:	SUBS R3, R3, #1			@ r3 = r3 - 1, decrement inner loop
		LDR R0, =input
		BNE _inner		@ repeat until r3 = 0
		BEQ _print

_exit:
        POP {PC}
        MOV PC, LR

_stop:
	LDR R0, =#0
	@BL E4235_KYBdeblock
	LDR R0, =input
	BL scanf
	
	LDR R0, =#1
	@BL E4235_KYBdeblock

.data
time:					
        .asciz "%02d:%02d:%02d\n"	@%02d will add padding 0s	
char:
	.asciz "%c"
input:
	.byte 0
run_char:
	.byte 'r'
lap_char:
	.byte 'l'
stop_char:
	.byte 's'
clr_char:
	.byte 'c'
test:
	.asciz "testing run state\n"
