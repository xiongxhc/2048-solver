#ifndef __LIST__
#define __LIST__

#include "node.h"

struct list{
    int size;
    int count;
    node_t** listarr;
};

#define initial_size 4

void list_init(struct list* l);

void list_pushback(struct list* l, node_t* value);

void emptyList(struct list* l);
#endif
