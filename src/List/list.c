#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "objects.h"

struct elem *initElem(void){
    struct elem *e = malloc(sizeof(struct elem));
    e->obj = EMPTY;
    e->prev = NULL;
    e->next = NULL;
    return e;
}

struct list *initList(void){
    struct list *l = malloc(sizeof(struct list));
    l->first = initElem();
    l->last = initElem();

    l->first->next = l->last;
    l->last->prev = l->first;
}

void add(struct list *ptr, enum objects obj){
    struct elem *newElem = initElem();
    newElem->obj = obj;

    ptr->last->prev->next = newElem;
    newElem->prev = ptr->last->prev;
    newElem->next = ptr->last;
    ptr->last->prev = newElem;
}

bool findType(struct list *ptr, enum objects obj){
    struct elem *e = ptr->first->next;
    while(e != ptr->last){
        if(e->obj == obj){
            return true;
        }
    }
    return false;
}