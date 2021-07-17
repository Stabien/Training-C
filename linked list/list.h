#ifndef LIST_H
#define LIST_H

typedef struct Element Element;
struct Element {
  int nb;
  Element *next;
  Element *previous;
};

typedef struct List List;
struct List {
  Element *first;
  Element *last;
};

#endif
