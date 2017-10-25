#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int x = 5;
	printf("%d\n",argc);
	char *name = malloc(4);
	strcpy(name, "Bob");
	printf("%s\n", name);
	return 0;	
}

