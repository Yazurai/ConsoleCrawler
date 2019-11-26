#ifndef DUNGEONCRAWLER_ENVIRONMENT_H
#define DUNGEONCRAWLER_ENVIRONMENT_H

#include "GameUtilities/position.h"
#include <stdint.h>
#include "GameUtilities/objects.h"

extern uint8_t treasureCount;

void setupTreasure(void);
void spawnPortal(void);
void decodeInput(char input[25][82]);
bool checkEnemy(struct position pos);
bool checkEnvironment(struct position pos, enum objects obj);

#endif //DUNGEONCRAWLER_ENVIRONMENT_H
