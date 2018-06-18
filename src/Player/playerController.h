#ifndef DUNGEONCRAWLER_PLAYERCONTROLLER_H
#define DUNGEONCRAWLER_PLAYERCONTROLLER_H

#include <stdint.h>
#include "position.h"

void burn(void);
void spawnPlayer(uint8_t x, uint8_t y);
void move(enum direction dir);

void *inputThread(void *arg);

#endif //DUNGEONCRAWLER_PLAYERCONTROLLER_H
