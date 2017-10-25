	.file "divd.S"
	.text
.global divd

divd:
	clr	r13      ; clear r13 (r means REGISTER)
loop:                    ; shell args loaded into 
                         ; >>> 15 (dividend)  and 14 (divisor)
	sub	r14, r15 ; subtract divisor from dividend
	inc	r13      ; increment counter 
	cmp	r14, r15 ; is dividend larger than divisor?
	jge	loop     ; if yes, jump to label "loop"
     ;jumpif >=
                         ; else

	clr	r14      ; clear divisor garbage
	mov	r15, r14 ; move remainder to 2nd location
	clr	r15      ; clear 1st location
	mov	r13, r15 ; quotient = counter
                         ; remainder == remainder
	ret

;                          help: list available commands
;                          args: print back given arguments
;                          divd: divide a number by another

;                          example input : divd 13 2
;                          example output: 6 1

