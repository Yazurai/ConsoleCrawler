#ifndef UNTITLED_UIUTILIES_H
#define UNTITLED_UIUTILIES_H

#include <stdint.h>
#include <windows.h>
#include "escCodes.h"
#include "position.h"

struct screenPos{
    uint8_t  x;
    uint8_t  y;
};

void print(position pos, fgColor fgC, bgColor bgC, char *text);

BOOL keyPressed(void);

#endif //UNTITLED_UIUTILIES_H
