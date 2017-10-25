#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR   = -1;
    P1OUT   = -1; // 0xFF, 0b11111111
    P2DIR   = -1;
    P2OUT   =  0;

    return 0;
}
