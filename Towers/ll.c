#include "ll.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
  LL *l = (LL *)malloc(sizeof(LL));
  if (l == NULL) {
    return NULL;
  }
  l->head = NULL;
  return l;
}

bool list_add(LL *l, item *i) {
  Node *n = (Node *)malloc(sizeof(Node));
  if(n == NULL) {
	  return false;
  }
  if (l->head == NULL){
	  l->head = n;
	  return true;
  }
  n->data = *i;
  n->next = l->head;
  l->head = n;
  return true;
}


item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
  Node *n = l->head;
  while (n != NULL) {
    if (cmp(&n->data, i)) {
      return &n->data;
    }
    n = n->next;
  }
  return NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
  Node *n = l->head;
  Node *prev = NULL;

  if (cmp(&(l->head->data), i)) {
	  l->head = n->next;
	  free(n);
	  return;
  } 

  while (n != NULL && !cmp(&n->data, i)){
    prev = n;
    n = n-> next;
  }

  if (prev != NULL) {
	  prev->next = n->next;
  }
  free(n); 
}

void list_destroy(LL **l) {
  Node *n, *next;
  for(n = (*l)->head; n != NULL; n = next) {
	  next = n->next;
	  free(n); 
  }
  free(*l);
  *l = NULL;
}

