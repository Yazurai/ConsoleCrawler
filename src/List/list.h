#ifndef DUNGEONCRAWLER_LIST_H
#define DUNGEONCRAWLER_LIST_H

#include "GameUtilities/objects.h"

struct elem{
    enum objects obj;
    struct elem *prev;
    struct elem *next;
};

struct list{
    struct elem *first;
    struct elem *last;
};

struct elem *initElem(void);

struct list *initList(void);

void add(struct list *ptr, enum objects obj);

bool findType(struct list *ptr, enum objects obj);

#endif //DUNGEONCRAWLER_LIST_H
