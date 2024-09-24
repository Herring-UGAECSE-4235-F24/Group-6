
	.global main
	.func main
main:
	PUSH {LR}
	LDR R0, =1
	BL E4235_KYBdeblock
	LDR R10, =684	@# of loops for .01 seconds
	BL clear
	
run:			@needs to keeps incrementing and printing until 'l' 's' or 'c' are pressed
	LDR R11, =1	@flag for printing or not. used to keep time
			@consistent between r and l mode.

run_loop:
	BL _inc		@runs the loops that increment the clock
	BL _print
	
	LDR R0, =char	@formatting scanf to take a char
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

lap:			@keep incrementing, but stop printing the time
	LDR R11, =0	@setting flag
	
	LDR R0, =printing
	LDM R0, {R1, R2, R3}
	MOV R3, R7
	MOV R2, R8
	MOV R1, R9
	STM R0, {R1, R2, R3}
lap_loop:
	BL _inc	
	BL _print
	
	LDR R0, =char
	LDR R1, =input
	BL scanf
	
	LDR R0, =input	@storing input
	LDRB R4, [R0]
	
	LDR R0, =run_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'r'
	BEQ run
	
	LDR R0, =stop_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 's'
	BEQ stop
	
	LDR R0, =clr_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'c'
	BEQ clear	@resets to 0:0:0
	
	BNE lap_loop
	
stop:			@stop incrementing, just display the time	
	LDR R11, =1
stop_loop:
	BL _print
	LDR R0, =char
	LDR R1, =input
	BL scanf
	
	LDR R0, =input	@storing input
	LDRB R4, [R0]
	
	LDR R0, =run_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'r'
	BEQ run
	
	LDR R0, =clr_char
	LDRB R5, [R0]
	CMP R4, R5	@checks if input is 'c'
	BEQ clear	@resets to 0:0:0
	BNE stop_loop

clear:
	LDR R11, =1
	LDR R6, =#0	@inner loops (counts up to 0.01 secs)
	LDR R7, =#0	@hundrendths
	LDR R8, =#0	@seconds
	LDR R9, =#0	@minutes
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
	
	CMP R11, #0		
	BNE r			@if not in lap mode, print current value
	LDR R0, =printing
	LDM R0, {R1, R2, R3}	@if in lap mode, print stored value
	B continue
r:      
	MOV R3, R7
	MOV R2, R8
	MOV R1, R9
continue:
	LDR R0, =time		@formatting string for the clock
        BL printf
			
	POP {LR}		@LR has been changed by BL printf. restoring it
	BX LR

_inc:	
	ADDS R6, R6, #1
	CMP R6, R10		@checking if .01 secs has passed

	BEQ _hunds		@if so, increment hunds
	BX LR			@if not, return to calling function

_hunds:
	SUBS R6, R6, R10	@resetting inner loops
	ADD R7, R7, #1		@increment hundrenths
	CMP R7, #100		
	BEQ _secs		@if a second has passed, increment
	BX LR			@if not, return
	
_secs:	
	SUBS R7, R7, #100	@resetting hundreths
	ADD R8, R8, #1		@increment seconds
	CMP R8, #60
	BEQ _mins		@if a min has passed, increment
	BX LR			@if not, return
_mins:
	SUBS R8, R8, #60	@resets seconds
	ADD R9, R9, #1		@increment minutes
	
	BX LR			@return

_exit:
        POP {PC}
        MOV PC, LR
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
.align
printing:
	.word 0, 0, 0			@storage for printing during l
					@these are arbitrary starting values
