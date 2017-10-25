#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Function declarations */
char chooseBase(int number, int base);
char base2(int number, int base, int count, int i);
char notBase2(int number, int base, int i);

/* Global variables */
char *ascii="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
char buffer[32];
int count=0;

/* Main function */
char main(int argc, const char **argv)
{
    /* Check for invalid number of arguments. */
    if (argc != 3)
    {
        printf("%s\n", "Usage: conv <decimal> <base>");
    }
    /* Check for invalid number. */
    else if (strlen(argv[1]) > 19)
    {
        printf("%s\n", "INVALID NUMBER");
    }
    /* Check for invalid base. */
    else if (! (                                    // If base is NOT
            (atoi(argv[2])>=2 && atoi(argv[2])<=16) // between 2 and 16 (incl)
            || atoi(argv[2])==64 ) )                // or equal to 64...
    {
       printf("%s\n", "INVALID BASE");            
    }
    /* Non-zero with valid number of arguments. */
    else if ((argc == 3) && (atoi(argv[1]) != 0))
    {
        int number = atoi(argv[1]); 
        int base = atoi(argv[2]);   
        chooseBase(number, base);  
    }
    /* Zero as integer input */
    else
    {
        printf("%d\n", 0);          
    }
    return 0;
}

/* Decides whether base is a power of two. */
char chooseBase(int number, int base)
{
    int i = 31;
    int baseChanger = base;
    while (((baseChanger % 2) == 0) && (baseChanger > 1))
    {
        baseChanger /= 2;
        count++;           // One shift per power of 2
    }
    if (baseChanger == 1)
        base2(number, base, count, i);      
    else
        notBase2(number, base, i);       
    return 0;
}

/* Function for bases which ARE powers of two. */
char base2(int number, int base, int shift, int i)
{
    int mask = base - 1;
    while (number > 0)                    
    {                                    
        buffer[i] = ascii[number & mask]; 
        number >>= shift;           
        i--;
     }
     printf("%s\n", &buffer[i + 1]);     
     return 0;
}

/* Function for bases which are NOT powers of two */
char notBase2(int number, int base, int i)
{
     while (number > 0)                  
    {                                    
        buffer[i] = ascii[number % base]; 
        number /= base;
        i--;
    }
    printf("%s\n", &buffer[i + 1]);      
    return 0;
}
