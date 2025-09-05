#ifndef _LL

#define _LL

#include "item.h"
#include <stdbool.h>

typedef struct Node Node;

struct Node {
  item data;
  Node *next;
  int id;
  int key; 
  int value; 
};

typedef struct LL LL;
struct LL {
  Node *head;
};

LL *list_create(void);
bool list_add(LL *l, item *);
item *list_find(LL *l, bool (*cmp)(item *, item *), item *i);

void list_destroy(LL **);
void list_remove(LL *l, bool (*)(item *, item *), item *);

#endif
