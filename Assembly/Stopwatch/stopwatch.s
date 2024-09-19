
	.global main
	.func main
main:
	PUSH {LR}
	LDR R0, =1
	BL E4235_KYBdeblock
	LDR R10, =684	@# of loops for .01 seconds while printing
	LDR R12, =684
	BL clear
	
run:			@needs to keeps incrementing and printing until 'l' 's' or 'c' are pressed
	LDR R11, =1	@flag for printing or not. used to keep time
	LDR R6, =0	@consistent between r and l mode.

run_loop:
	BL _inc		@runs the loops that increment the clock
	BL _print
	
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

lap:			@keep incrementing, but stop printing the time
	LDR R11, =0
	LDR R6, =0

lap_loop:
	BL _inc	
	
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
	BNE stop

clear:
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
	
        LDR R0, =time		@formatting printf        
        MOV R3, R7
	MOV R2, R8
	MOV R1, R9
        BL printf
			
	POP {LR}		@LR has been changed by BL printf. restoring it
	BX LR

_inc:	ADDS R6, R6, #1

	@CMP R11, #1		@check if in r or l
	@BEQ r			@if r, use R10. if l use R12
	@CMP R6, R12
	@B continue
r:	
	CMP R6, R10		@checking if .01 secs has passed
continue:
	BEQ _hunds		@if so, increment hunds
	BX LR			@if not, return to calling function

_hunds:
	@CMP R11, #1
	@BEQ runs
	@SUBS R6, R6, R12
	@B continue2
runs:	
	SUBS R6, R6, R10	@resetting inner loops
continue2:
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
test:
	.asciz "running"
