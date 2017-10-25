#include <stdio.h>
#include "functions.h"

//extern char *ascii;
//extern char buffer[];
//char *ascii;
//char buffer[];

/* For bases which are NOT powers of two. */
char notBase2(int number, int base, int i, struct vars)
{
    while (number > 0)
    {
        vars.buffer[i] = vars.ascii[number % base];
        number /= base;
        i--;
    }
    printf("%s\n", vars.buffer[i + 1]);
    return 0;
}
