#ifndef DUNGEONCRAWLER_ENEMY_H
#define DUNGEONCRAWLER_ENEMY_H

#include "position.h"

struct enemy{
    struct position pos;
    char skin;
};

void newEnemy(struct enemy *ptr, struct position pos, char skin);

void renderEnemy(struct enemy *ptr);

void moveEnemy(struct enemy *ptr, enum direction dir);

void *updateEnemyThread(void *arg);

#endif //DUNGEONCRAWLER_ENEMY_H
