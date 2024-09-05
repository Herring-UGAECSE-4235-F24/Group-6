/* Attempting to output loop counter with printf */

        .global main
        .func main

main:
        LDR R0, =fmtInput
        LDR R1, =num
        BL scanf
        
        LDR R1, =num
        LDR R1, [R1]

.data
message:        .asciz "Hello world\n"
fmtInput:       .string "%d"
.align 2
num:    .word 1
