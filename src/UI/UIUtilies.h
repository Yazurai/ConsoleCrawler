#ifndef UNTITLED_UIUTILIES_H
#define UNTITLED_UIUTILIES_H

#include <stdint.h>
#include <stdbool.h> 
#include "UI/escCodes.h"
#include "GameUtilities/position.h"

struct screenPos{
    uint8_t  x;
    uint8_t  y;
};

void print(position pos, fgColor fgC, bgColor bgC, char *text);

#endif //UNTITLED_UIUTILIES_H
