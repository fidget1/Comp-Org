#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char chooseBase(int number, int base);
//char base2(int mask, int number, int i, int shift);
//char notBase2(int number, int base, int i);

/* Global variables */
char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
char buffer[32];

/* Main procedure */
char main(int argc, const char **argv)
{
    /* Check for invalid number of arguments. */
    if (argc != 3)
    {
        printf("%s\n", "Usage: conv <decimal> <base>");
    }
    /* Non-zero with valid number of arguments. */
    else if ((argc == 3) & (atoi(argv[1]) != 0))
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
/*
// Procedure to choose base.
char chooseBase(int number, int base)
{
    int i = 31;
    switch (base)
    {
        // Power of two bases (mask and shift algorithm) 
        // Parameters: (mask, number, counter, shift)    
        case 2 :      
            base2(0x1, number, i, 1);
            break;
        case 4 :
            base2(0x3, number, i, 2);
            break;
        case 8 :
            base2(0x7, number, i, 3);
            break;
        case 16 :
            base2(0xf, number, i, 4);
            break;
        case 64 : 
            base2(0x3f, number, i, 6);
            break;

        // Not power of two bases. 
        case 3 : 
        case 5 ... 7 :
        case 9 ... 15 :
            notBase2(number, base, i);
            break;

        // Base not 2-16 or 64. 
        default :   
            printf("%s\n", "INVALID BASE");
            break;
    }  
    return 0;
}   

// For bases which ARE powers of two. 
char base2 (int mask, int number, int i, int shift)
{
    while (number > 0)
    {
        buffer[i] = ascii[(number & mask)];
        number = number >> shift;
        i--;
     }
     printf("%s\n", &buffer[i + 1]);
     return 0;
}

// For bases which are NOT powers of two. 
char notBase2(int number, int base, int i)
{
    while (number > 0)    
    {
        buffer[i] = ascii[(number % base)];
        number /= base;
        i--;
    }
    printf("%s\n", &buffer[i + 1]);
    return 0;
}
*/
