#ifndef DUNGEONCRAWLER_ENVIRONMENT_H
#define DUNGEONCRAWLER_ENVIRONMENT_H

#include "position.h"
#include <stdint.h>

extern uint8_t treasureCount;

void setupTreasure(void);
void decodeInput(char input[25][82]);
bool checkWall(struct position pos);
bool checkEnemy(struct position pos);
bool checkHealthPack(struct position pos);
bool checkShield(struct position pos);
bool checkTreasure(struct position pos);
bool checkEmpty(struct position pos);

#endif //DUNGEONCRAWLER_ENVIRONMENT_H
