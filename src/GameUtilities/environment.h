#ifndef DUNGEONCRAWLER_ENVIRONMENT_H
#define DUNGEONCRAWLER_ENVIRONMENT_H

#include "position.h"

void decodeInput(char input[25][82]);
bool checkWall(struct position pos);
bool checkEnemy(struct position pos);
bool checkHealthPack(struct position pos);
bool checkShield(struct position pos);

#endif //DUNGEONCRAWLER_ENVIRONMENT_H
