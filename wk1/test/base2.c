#include <stdio.h>
#include "functions.h"

//extern char *ascii;
//extern char buffer[];
//char *ascii;
//char buffer[];

/* For bases which ARE powers of two. */
char base2 (int mask, int number, int i, int shift, vars)
{
    while (number > 0)
    {
        vars.buffer[i] = ascii[number & mask];
        number >>= shift;
        i--;
     }
     printf("%s\n", vars.buffer[i + 1]);
     return 0;
}
