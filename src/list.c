#include "list.h"
#include "utils.h"

void list_init(struct list* l){
    int i;

    l->count = 0;
    l->size = initial_size;
    l->listarr = (node_t **) malloc(sizeof(node_t) * initial_size);

    for(i = 0; i < initial_size; i++)
        l->listarr[i] = NULL;

    if(!l->listarr){
        printf("Error allocating a memory..\n");
        exit(-1);
    }
}

void list_pushback(struct list* l, node_t* value){

    if(l->count == l->size){
        l->size += 1;
        l->listarr = realloc(l->listarr, sizeof(node_t) * l->size);
        if(!l->listarr) exit(-1);
    }
    l->count++;
    l->listarr[l->count] = value;
}

node_t* list_delete(struct list* l){
    node_t* removed;
    node_t* temp = l->listarr[--l->count];

    if((l->count <= (l->size + 2)) && (l->size > initial_size)){
        l->size -= 1;
        l->listarr = realloc(l->listarr, sizeof(node_t) * l->size);
        if (!l->listarr) exit(-1);
    }
    removed = l->listarr[0];
    l->listarr[0] = temp;
    if(temp == removed) l->listarr[0] = 0;
    return removed;
}

void emptyList(struct list* l){
    while(l->count != 0){
        node_t* n = list_delete(l);
        free(n);
    }
}
