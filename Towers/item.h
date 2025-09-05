#ifndef _ITEM
#define _ITEM

#include <stdbool.h>

// typedef int item;

typedef struct item item;

struct item {
  char key[256];
  int id;
  int value; 
};

bool cmp(item *i1, item *i2);

#endif
