#ifndef DUNGEONCRAWLER_POSITION_H
#define DUNGEONCRAWLER_POSITION_H

#include <stdint.h>

struct position{
    uint8_t x;
    uint8_t y;
};

enum direction{
    UP = 65, RIGHT = 67, DOWN = 66, LEFT = 68
};

#endif //DUNGEONCRAWLER_POSITION_H
