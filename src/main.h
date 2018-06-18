#ifndef DUNGEONCRAWLER_MAIN_H
#define DUNGEONCRAWLER_MAIN_H

#include <stdbool.h>
#include "Enemy/enemy.h"

extern struct enemy enemies[20];
extern bool shouldStop;

bool checkWall(struct position pos);

#endif //DUNGEONCRAWLER_MAIN_H
