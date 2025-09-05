#ifndef _HASH

#define _HASH

#include "ll.h"

#define BUCKETS 101

typedef struct Hashtable Hashtable;

struct Hashtable {
  // your datastructure here; this is just a placeholder
  // int h;
  LL *l[BUCKETS];
  int key; 
  int value; 
  int id;
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *h, char *key, int val);

int *hash_get(Hashtable *h, char *key);

void hash_destroy(Hashtable *h);

#endif
