/******
 *
 *    MACALLISTER ARMSTRONG - ASSIGNMENT 4
 *
 ******/
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include <libemb/shell/shell.h>
/******
 *
 *    CONSTANTS
 *
 ******/
#define NUM_DIGITS 4
/******
 *
 *    GLOBALS
 *
 ******/
int digit  = 0;
char *input;
static const char hex[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
                             0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
/******
 *
 *    PROTOTYPES
 *
 ******/
int shell_cmd_help(shell_cmd_args *args);
int shell_cmd_argt(shell_cmd_args *args);
int shell_cmd_hexd(shell_cmd_args *args);
/******
 *
 *    SHELL COMMANDS STRUCT
 *
 ******/
shell_cmds my_shell_cmds = {
  .count = 3,
  .cmds  = {
    {
      .cmd  = "help",
      .desc = "list available commands",
      .func = shell_cmd_help
    },
    {
      .cmd  = "args",
      .desc = "print back given arguments",
      .func = shell_cmd_argt
    },
    {
      .cmd  = "hexd",
      .desc = "display two characters as hex bytes on the display",
      .func = shell_cmd_hexd
    },
  }
};
/******
 *
 *    CALLBACK HANDLERS
 *
 ******/
int shell_cmd_help(shell_cmd_args *args)
{
  int k;

  for(k = 0; k < my_shell_cmds.count; k++) {
    cio_printf("%s: %s\n\r", my_shell_cmds.cmds[k].cmd, my_shell_cmds.cmds[k].desc);
  }

  return 0;
}

int shell_cmd_argt(shell_cmd_args *args)
{
  int k;

  cio_print((char *)"args given:\n\r");

  for(k = 0; k < args->count; k++) {
    cio_printf(" - %s\n\r", args->args[k].val);
  }

  return 0;
}

int shell_cmd_hexd(shell_cmd_args *args)
{
  input = args->args[0].val;                // Store characters in an array

  return 0;
}

int shell_process(char *cmd_line)
{
  return shell_process_cmds(&my_shell_cmds, cmd_line);
}
/******
 *
 *    INITIALIZATION
 *
 ******/
int main(void)
{
  /* CLOCKS *********************************/
  WDTCTL   = WDTPW | WDTHOLD;               // Disable Watchdog
  BCSCTL1  = CALBC1_1MHZ;                   // Run @ 1MHz
  DCOCTL   = CALDCO_1MHZ;
  /* GPIO ***********************************/
  P1DIR = BIT4 | BIT5 | BIT6 | BIT7;        // Enable display outputs
  P1OUT = BIT4 | BIT5 | BIT6 | BIT7;        // Use as GPIO (output) pins
  P2SEL &= ~(BIT6 | BIT7);                  // XIN/XOUT G segment and colon pins
  P2DIR = BIT7;                             // Enable colon
  P2OUT = BIT7;                             // Turn on colon
  /* BUTTON *********************************/ 
  P1REN  = BIT3;                            // Button resistor enable
  P1OUT |= BIT3;                            // Set button tweaker
  P1IE  |= BIT3;                            // Enable interrupt
  P1IES |= BIT3;                            // Pull up resistor edge select
  P1IFG &= ~BIT3;                           // Clear interrupt flag
  /* TIMER A0 *******************************/
  TA0CTL   = TASSEL_2 | MC_1 | ID_3;        // Timer setup
  TA0CCTL0 = CCIE;                          // Interrupt enable (capture/compare)
  TA0CCR0  = 500;                           // Set period

  serial_init(9600);                        // Initialize Serial Comms
  __eint();                                 // Enable Global Interrupts
  
/******
 *
 *    PROGRAM LOOP
 *
 ******/
  for (;;) {
    int j = 0;                              // Char array counter
    char cmd_line[90] = {0};                // Init empty array

    cio_print((char *) "$ ");               // Display prompt
    char c = cio_getc();                    // Wait for a character
    while(c != '\r') {                      // until return sent then ...
      if(c == 0x08) {                       //  was it the delete key?
        if(j != 0) {                        //  cursor NOT at start?
          cmd_line[--j] = 0;                //  delete key logic
          cio_printc(0x08); 
          cio_printc(' '); 
          cio_printc(0x08);
        }
      } else {                              // otherwise ...
        cmd_line[j++] = c; 
        cio_printc(c);                      //  echo received char
      }
      c = cio_getc();                       // Wait for another
    }

    cio_print((char *) "\n\n\r");           // Delimit command result

    switch(shell_process(cmd_line))         // Execute specified shell command
    {                                       // and handle any errors
      case SHELL_PROCESS_ERR_CMD_UNKN:
        cio_print((char *) "ERROR, unknown command given\n\r");
        break;
      case SHELL_PROCESS_ERR_ARGS_LEN:
        cio_print((char *) "ERROR, an arguement is too lengthy\n\r");
        break;
      case SHELL_PROCESS_ERR_ARGS_MAX:
        cio_print((char *) "ERROR, too many arguements given\n\r");
        break;
      default:
        break;
    }
    P2DIR |= -1;                            // Enable outputs AFTER getting chars
    cio_print((char *) "\n");               // Delimit Result
  }
  return 0;
}

/******
 *
 *    INTERRUPTS
 *
 ******/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{

  switch (digit) {
    case 0:                                      // First Display 
    {
      P1OUT = BIT3;
      P1OUT |= BIT4;
      if (!(input[0] & 0xF0)) {
        P2OUT = ~0x00;
      } else {
        P2OUT = ~hex[(input[0] >> 4)];
      }
    }   
    break;
    case 1:                                       // Second Display 
    {
      P1OUT = BIT3;
      P1OUT |= BIT5;
      if (!(input[0] & 0xFF)) {
        P2OUT = ~0x00;
      } else {
        P2OUT = ~hex[(input[0] & 0x0F)];
      }
    } 
    break;
    case 2:                                       // Third Display 
    {
      P1OUT = BIT3;
      P1OUT |= BIT6;
      if (!(input[1] & 0xF0)) {
        P2OUT = ~0x00;
      } else {
        P2OUT = ~hex[(input[1] >> 4)];
      }
    }
    break;
    case 3:                                        // Fourth Display 
    {
      P1OUT = BIT3;
      P1OUT |= BIT7;
      if (!(input[1] & 0xFF)) {
        P2OUT = ~0x00;
      } else {
        P2OUT = ~hex[(input[1] & 0x0F)];
      }
    } 
    break;
  }
  ++digit;                                  // Increment Counter 0..3
  digit %= NUM_DIGITS;                      // Repeat
}

#pragma vector=PORT1_VECTOR
__interrupt void modeSwitch(void)
{
  TA0CTL = MC_0;                            // Turn off timer
  P2OUT = 255;                              // Clear displays
}
