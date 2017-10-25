;------------------------------------------------------------------------------
;   Digital I/O example for the LaunchPad
;   Read the status of built in push button - P1.3
;      (Note that P1.3 is "1" when the push button is open 
;       and "0" when the button is closed)
;   Red light if the button is not pushed - P1.0
;   Green light if the button is pushed - P1.6
;   Build with Code Composer Studio
;------------------------------------------------------------------------------

            .cdecls C,LIST,"msp430g2231.h"  ; cdecls tells assembler to allow
                                            ; the c header file

;------------------------------------------------------------------------------
;   Main Code
;------------------------------------------------------------------------------

            .text                           ; program start
            .global _main		    ; define entry point

_main       mov.w   #0280h,SP               ; initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; stop watchdog timer

            bis.b   #01000001b,&P1DIR       ; make P1.0 and P1.6 output
                                            ; all others are inputs by default

Mainloop    bit.b   #00001000b,&P1IN        ; read switch at P1.3
            jc      Off                     ; if P1.3 open branch to Off label
                                            
On          bic.b   #00000001b,&P1OUT       ; clear P1.0 (red off)
            bis.b   #01000000b,&P1OUT       ; set P1.6 (green on)
            jmp     Wait                    ; branch to a delay routine

Off         bis.b   #00000001b,&P1OUT       ; set P1.0 (red on)
            bic.b   #01000000b,&P1OUT       ; clear P1.6 (green off)
            
Wait        mov.w   #1834,R15               ; load R15 with value for delay
L1          dec.w   R15                     ; decrement R15
            jnz     L1                      ; if R15 is not zero jump to L1
            jmp     Mainloop                ; jump to the Mainloop label
                                            
;------------------------------------------------------------------------------
;   Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  _main                  

            .end
