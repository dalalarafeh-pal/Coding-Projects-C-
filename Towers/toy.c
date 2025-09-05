#include "item.h"
#include "ll.h"
#include <stdio.h>

#define MAGICN 457

int main() {
  LL *l = list_create();
  for (int i = 0; i < 1000; i++) {
    item item = {.id = i};
    sprintf(item.key, "%d", i);
    list_add(l, &item);
    // list_add(l, &i);
  }

  // item i = MAGICN;
  // list_remove(l, cmp, &i);

  item mItem;
  list_remove(l, cmp, &mItem);

  // int *ret;
  item *ret;
  for (int i = 0; i < 1000; i++) {
    if (i != MAGICN) {
      // ret = list_find(l, cmp, &i);
      sprintf(mItem.key, "%d", i);
      ret = list_find(l, cmp, &mItem);
      if (ret == NULL) {
        printf("something went wrong. I inserted %d into the list but then "
               "could not find it.\n",
               i);
        return 1;
      }
    }
  }
  list_destroy(&l);
  return 0;
}
