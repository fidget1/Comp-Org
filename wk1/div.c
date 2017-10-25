#include <stdio.h>
#include <stdlib.h>

void main(int argc, const char **argv)
{
  int digits[16];
  int number1 = atoi(argv[1]);
  int number2 = atoi(argv[2]);
  int whole = number1/number2;
  int rem = number1%number2; 
  int dig;
  printf("%d.", whole);
  for (int i = 0; i < 16; i++) 
  {
    dig = 10*rem/number2;
    digits[i] = dig;
    rem = 10*rem%number2;
    printf("%d", digits[i]);
  }
  printf("\n");
}
