@This is a delay program for 4230.  Your RP4 either runs at 1.5 or 1.8GHZ.  Using the program determine what speed your PI appears to be running
@Deliverable 1:  Calculate your RP4 clock speed.  Show how.
@Now let's make a stopwatch.   Use RP9:RP8:RP7 for minutes:seconds:hundredths of seconds.  Output the free running time to the terminal.  At 2:00:000, the stopwatch should go back to 0:00:00 and keep running.
@You should look at the printloop.s example for the use of the printf command.  You will probably need to investigate formating using the asciz data type.
@Deliverable 2: your code on github and in your writeup.  We will check in class and look at accuracy as well.

	.global main
    .func main

main:
        PUSH {LR}
        BAL _print
	LDR R7, =#0	@ hundrendths
	LDR R8, =#0	@ seconds
	LDR R9, =#0	@ minutes

_print:
        LDR R0, =string		@formatting printf        
        MOV R3, R7
	MOV R2, R8
	MOV R1, R9
        BL printf

	ADD R7, R7, #1
	CMP R7, #100
	BEQ _hunds
	BNE _loop
	
_hunds:	
	SUBS R7, R7, #100
	ADD R8, R8, #1
	CMP R8, #60
	BEQ _secs
	BNE _loop
_secs:
	SUBS R8, R8, #60
	ADD R9, R9, #1
	CMP R9, #2
	BEQ _done
	BNE _loop
_done:
        SUBS R9, R9, #2
	B _loop
	
_loop:	
		LDR R3, =8826100		@ r1 = 1,000,000,000 (inner loop count)
_inner:	SUBS R3, R3, #1			@ r3 = r3 - 1, decrement inner loop
		BNE _inner				@ repeat until r3 = 0
		BEQ _print

_exit:
        POP {PC}
        MOV PC, LR

.data
string:
        .asciz "%02d:%02d:%02d\n"
iterations:
        .word 15                 @ outer loop iterations
