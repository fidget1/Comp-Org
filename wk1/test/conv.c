#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//struct variable
//{
//  char buffer[32];
//  char *ascii;
//}vars;

//char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
//char buffer[32];

/* Main procedure */
char main(int argc, const char **argv)
{
    //vars.*ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    /* Check for invalid number of arguments. */
    if (argc != 3)
    {
        printf("%s\n", "Usage: conv <decimal> <base>");
    }
    /* Non-zero with valid number of arguments. */
    else if ((argc == 3) && (atoi(argv[1]) != 0))
    {
        /* Local variables */
        int number = atoi(argv[1]); // Number from input
        int base = atoi(argv[2]);   // Base
        chooseBase(number, base);
    }
    /* Zero */
    else
    {
        printf("%d\n", 0);
    }
    return 0;
}

//struct st
//{
//  char buffer[32];
//};
