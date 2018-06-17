#ifndef DUNGEONCRAWLER_PLAYERCONTROLLER_H
#define DUNGEONCRAWLER_PLAYERCONTROLLER_H

#include <stdint.h>
#include "position.h"

void spawnPlayer(uint8_t x, uint8_t y);
void move(enum direction dir);

#endif //DUNGEONCRAWLER_PLAYERCONTROLLER_H
