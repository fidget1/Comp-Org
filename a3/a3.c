/* Macallister Armstrong
   Assignment 3

*/
#include <msp430.h> 

int mode = 0;
int flip = 0;

int init(void)
{
    // Watch dog timer things
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    // Enable port 1, Clear pin outputs
    P1DIR = 0x3;
    P1OUT = 0;

    // Enable pull-up resistor, select it,
    // enable interrupt, set edge select,
    // clear interrupt flag
    P1REN  = BIT3;
    P1OUT |= BIT3;
    P1IE  |= BIT3;
    P1IES |= BIT3;
    P1IFG &= ~BIT3; 
   
    // Enable P1.6 too, select it
    P1DIR |= BIT6;
    P1SEL |= BIT6;

    // TIMER A0 control register =
    // select SMCLK as timer source |
    // enable capture/compare interrupt
    // set period for capture control register to 1/3 second                        
    TA0CTL   = TASSEL_2 | MC_1 | ID_3;
    TA0CCTL0 = CCIE;
    TA0CCR0  = 41667;

    //Enable P2.1, select it
    P2DIR |= BIT1;
    P2SEL |= BIT1;

    // TIMER A1 control register + 
    // select SMCLK as a timer source
    // enable capture/compare interrupt
    // set period for capture control register to 1/4 second                        
    TA1CTL   = TASSEL_2 | MC_1 | ID_3;
    TA1CCTL0 = CCIE;
    TA1CCR0  = 31250;       

    // _ BITSELECT _ STATUS REGISTER ( GIE == BIT3 == Global interrupt enable )
    _BIS_SR(GIE);
    
    return 0;
}


int main(void)
{
    // Initialize timers and things
    init();

    for (;;) {
        // Clear P1.0 and P1.1 
        P1OUT &= ~0x3;
        // Toggle red light ad infinitum
        while(mode == 0) {
            __delay_cycles(500000);
            P1OUT ^= BIT0;
        }
        // Clear P1.0 and P1.1 
        P1OUT &= ~0x3;
        while(mode == 1) {
            // Toggle output - Green
            TA0CCTL1 = OUTMOD_4;
            // Toggle red light ad infinitum
            __delay_cycles(500000);
            P1OUT ^= BIT0;
        }
        // Clear P1.0
        P1OUT &= ~1;
        while (mode == 2) {
            // Toggle output - Blue
            TA1CCTL1 = OUTMOD_4;
        }
        // Clear P1.0 and P1.1
        P1OUT &= ~0x3;
        // Turn off blue output
        TA1CCTL1 &= ~OUTMOD_4;
        while (mode == 3) {
            // Set capture/control register's period to 1/2 second
            TA1CCR0 = 62500;
            // Turn on blue output
            TA1CCTL1 = OUTMOD_4;
        }
        // Turn blue output off
        TA1CCTL1 &= ~OUTMOD_4;
    }
    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void blink(void)
{
    // Flip the green light on/off
    if (mode == 1 || mode == 2) {
        P1OUT ^= BIT1;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void modeSwitch(void)
{
    // Flip red and green
    P1OUT &= ~0x3;
    // Increment
    mode++;
    // Counts 00,01,10,11 and repeats
    // I'm not sure why mode++ works here.
    if (mode++ % 2 == 1) {
        mode ^= BIT1 | BIT0;
    } else { 
        mode ^= BIT0;
    }
    while (!(BIT3 & P1IN)) {}
    __delay_cycles(31250);
    P1IFG &= ~BIT3;
    mode %= 4;
}
