#include <stdio.h>
#include <stdlib.h>

struct bike {
  int gear;
  int wheels;
  char* name;
};

//typedef struct bike bike;

int main(void) {
  struct bike *my_bike = malloc(sizeof(struct bike));

  (*my_bike).gear = 3;
  my_bike->wheels = 2;
  my_bike->name = "Macallister";

  printf("GEARS: %d\nWHEELS: %d\nNAME: %s\n", 
    my_bike->gear, my_bike->wheels, my_bike->name);
}
