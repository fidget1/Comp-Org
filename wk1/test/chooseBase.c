#include <stdio.h>
#include "functions.h"

/* Procedure to choose base. */
char chooseBase(int number, int base)
{
    int i = 31;
    switch (base)
    {
        /* Power of two bases (mask and shift algorithm) */
        /* Parameters: (mask, number, counter, shift)    */
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

        /* Not power of two bases. */
        case 3 :
        case 5 ... 7 :
        case 9 ... 15 :
            notBase2(number, base, i);
            break;

        /* Base not 2-16 or 64. */
        default :
            printf("%s\n", "INVALID BASE");
            break;
    }
    return 0;
}
