#ifndef UNTITLED_UIUTILIES_H
#define UNTITLED_UIUTILIES_H

#include <stdint.h>
#include <windows.h>
#include "escCodes.h"

struct screenPos{
    uint8_t  x;
    uint8_t  y;
};

void setCursorPos(uint8_t x, uint8_t y);

void setFgColor(enum fgColor color);
void setBgColor(enum bgColor color);

BOOL keyPressed(void);

#endif //UNTITLED_UIUTILIES_H
