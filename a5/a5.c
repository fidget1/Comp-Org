#include "dtc.h"
#include <msp430g2553.h>

/*****************************************************************
  CONSTANTS                                                      
 *****************************************************************/
const char digit[] = {BIT5, BIT6, BIT7};

const char GR1[] = {BIT1, 0x00};
const char GR2[] = {0x6D, 0xC0};

const char P1num[] = { /* BIT1 = Bseg
    0 */ BIT1, /* Numeric Display
    1 */ BIT1, /*
    2 */ BIT1, /*
    3 */ BIT1, /*
    4 */ BIT1, /*
    5 */ 0x00, /*
    6 */ 0x00, /*
    7 */ BIT1, /*
    8 */ BIT1, /*
    9 */ BIT1, /*
    A */ BIT1, /*
    b */ 0x00, /*
    c */ 0x00, /*
    d */ BIT1, /*
    E */ 0x00, /*
    F */ 0x00, 
};

const char P2num[] = { /*  EGFx DCxA
    0 */ 0xAD, /* Numeric Display
    1 */ 0x04, /*
    2 */ 0xC9, /*
    3 */ 0x4D, /*
    4 */ 0x64, /*
    5 */ 0x6D, /*
    6 */ 0xED, /*
    7 */ 0x05, /*
    8 */ 0xED, /*
    9 */ 0x65, /*
    A */ 0xE5, /*
    b */ 0xEC, /*
    c */ 0xA9, /*
    d */ 0xCC, /*
    E */ 0xE9, /*
    F */ 0xE1, //
};

/***************************************************************
 GLOBALS
 ***************************************************************/
unsigned number = 0;
int mode = 0;
int cursor = 1;

int main(void) {

  /************************************************************
   INITIALIZATION
   ************************************************************/
  initialize_dtc(INCH_4, &number);

  WDTCTL = WDTPW | WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

 /***********************************************************
   PORT1 INITIALIZATION
  ***********************************************************/
  P1DIR  = 0xE6; // No button, no potentiometer, no BIT0
  P1SEL |= BIT2; // RED selected for PWM stuff              
  P1OUT  = 0x06; // Turn on RED/turn off B segment
  
  P1REN  =  BIT3; // Enable pull up resistor
  P1OUT |=  BIT3; // Input is a go
  P1IE  |=  BIT3; // Interrupt something r other
  P1IES |=  BIT3; // Same
  P1IFG &= ~BIT3; // Clear interrupt flag

 /***********************************************************
   PORT2 INITIALIZATION
  ***********************************************************/
  P2DIR  = 0xFF;  // All segments and PWM output

  P2SEL  =   BIT1 | BIT4;  // GREEN and BLUE
  P2SEL &= ~(BIT6 | BIT7); // Enable 2.6 and 2.7 as GPIO

  P2OUT  = 0xED;  // Turn off segments
 /***********************************************************
   TIMER
  ***********************************************************/
  TA0CCTL0 = CCIE;            // Capture/compare interrupt enable
  TA0CTL   = TASSEL_2 | MC_1; // | ID_3; // SMCLK | up to CCR0 | 8 divider
  TA0CCR0  = 1023;            // Set period 
  TA0CCTL1 = OUTMOD_7;        // PWM reset/set
  TA0CCR1  = 0;               // Set PW in program loop?

  TA1CTL   = TASSEL_2 | MC_1; // | ID_3; // SMCLK | up to CCR0 | 8 divider
  TA1CCR0  = 1023;            // Set period 
  TA1CCTL1 = OUTMOD_7;        // PWM reset/set
  TA1CCTL2 = OUTMOD_7;        // PWM reset/set
  TA1CCR1  = 0;               // Set PW
  TA1CCR2  = 0;               // Set PW

  _BIS_SR(GIE);               // Global interrupt enable
 /***********************************************************
   PROGRAM LOOP
  ***********************************************************/
  for(;;) {;}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  int n = number >> 2;
  P1OUT |=  BIT1;                 // B segment off
  P1OUT &= ~(BIT5 | BIT6 | BIT7); // Displays off

  P2OUT |= 0xED;                  // Segments off

  switch (mode) {
    case 0:
      TA0CCR1 = number;
      break;
    case 1:
      TA1CCR1 = number;
      break;
    case 2:
      TA1CCR2 = number;
      break;
  }

  switch (cursor) {
    case 0:
      P1OUT |= digit[0];
      switch (mode) {
        case 0:
          P1OUT &= ~GR1[1];
          P2OUT &= ~GR2[1];
          break;
        case 1:
          P1OUT &= ~GR1[0];
          P2OUT &= ~GR2[0];
          break;
        case 2:
          P1OUT &= ~P1num[11];
          P2OUT &= ~P2num[11];
          break;
      }
      break;
    case 1:
      P1OUT |= digit[1];
      P1OUT &= ~P1num[n / 0x10   % 0x10];
      P2OUT &= ~P2num[n / 0x10   % 0x10];
      break;
    case 2:
      P1OUT |= digit[2];
      P1OUT &= ~P1num[n          % 0x10];
      P2OUT &= ~P2num[n          % 0x10];
      break;
  }
  cursor++;
  cursor %= 3;
}

#pragma vector=PORT1_VECTOR
__interrupt void modeSwitch(void)
{
  while (!(BIT3 & P1IN)) {}
  __delay_cycles(31250);
  P1IFG &= ~BIT3;

  mode++;
  mode %= 3;
 
}

