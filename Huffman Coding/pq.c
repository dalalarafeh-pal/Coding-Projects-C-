#include "pq.h"
#include "node.h"
#include <stdio.h>

typedef struct ListElement ListElement;
struct ListElement {
  Node *tree;
  ListElement *next;
};

struct PriorityQueue {
  ListElement *list;
};

PriorityQueue *pq_create(void) {
  PriorityQueue *q = (PriorityQueue *)calloc(1, sizeof(PriorityQueue));
  if (q == NULL) {
    return NULL;
  }

  q->list = NULL;
  return q;
}

void pq_free(PriorityQueue **q) {
  if (*q == NULL) {
    return;
  }
  ListElement *e = (*q)->list;
  while (e != NULL) {
    node_free(&(e->tree));
    e = e->next;
  }
  free(*q);
  *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
  if (q == NULL || q->list == NULL) {
    return true;
  }
  return false;
}

bool pq_size_is_1(PriorityQueue *q) {
  return q->list != NULL && q->list->next == NULL;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
  if (e1->tree->weight < e2->tree->weight) {
    return true;
  } else if (e1->tree->weight == e2->tree->weight) {
    return (e1->tree->symbol < e2->tree->symbol);
  } else {
    return false;
  }
}

void enqueue(PriorityQueue *q, Node *tree) {
  ListElement *newe = (ListElement *)calloc(1, sizeof(ListElement));
  if (newe == NULL) {
    return;
  }

  newe->tree = tree;

  if (pq_is_empty(q) || pq_less_than(newe, q->list)) {
    newe->next = q->list;
    q->list = newe;
  } else {
    ListElement *prev = q->list;
    while (prev->next != NULL && pq_less_than(prev->next, newe)) {
      prev = prev->next;
    }
    newe->next = prev->next;
    prev->next = newe;
  }
}

Node *dequeue(PriorityQueue *q) {
  if (pq_is_empty(q)) {
    fprintf(stderr, "Error: Empty Queue.\n");
    return NULL;
  }

  ListElement *front = q->list;
  Node *tree = front->tree;
  q->list = front->next;
  free(front);
  return tree;
}

void pq_print(PriorityQueue *q) {
  assert(q != NULL);
  ListElement *e = q->list;
  int position = 1;

  while (e != NULL) {
    if (position++ == 1) {
      printf("=============================================\n");
    } else {
      printf("---------------------------------------------\n");
    }
    node_print_tree(e->tree);
    e = e->next;
  }
  printf("=============================================\n");
}
