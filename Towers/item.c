#include "item.h"
#include "hash.h"
#include "ll.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// implementation of the cmp() function on items, for when items are ints
// bool cmp(item *i1, item *i2) { return(*i1 == *i2); }

bool cmp(item *i1, item *i2){
       	return strcmp(i1->key, i2->key) == 0; 
}
