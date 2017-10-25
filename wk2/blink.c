#include <msp430.h>

int main(void) {
	WDTCTL = WDTHOLD | WDTPW;
        BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

/*	P1DIR = 0x1;
	P1OUT = 0x1;
	P2DIR = 0x1;
	P2OUT = 0x1;
*/

	P1DIR |= (BIT0 | BIT6);

for (;;) {
/*
	P1OUT = 0x0;
	P2OUT = 0x1;
	__delay_cycles(1000000);
	P1OUT = 0x1;
	P2OUT = 0x0;
	__delay_cycles(1000000);
*/
	P1OUT ^= (BIT0 | BIT6);
	__delay_cycles(1000000);
}

	return 0;
}
