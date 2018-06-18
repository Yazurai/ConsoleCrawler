#include "UIUtilies.h"
#include "position.h"
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

void setCursorPos(uint8_t x, uint8_t y){
    printf("%c[%d;%dH", ESCAPE, y, x);
}

void setFgColor(enum fgColor color){
    printf("%c[%dm", ESCAPE, color);
}

void setBgColor(enum bgColor color){
    printf("%c[%dm", ESCAPE, color);
}

void moveCursor(enum direction dir, uint8_t amount){
    printf("%c[%d%c", ESCAPE, amount, dir);
}

BOOL keyPressed(void) {
    for(int i = 0; i<256; i++)
        if(GetAsyncKeyState(i) >> 8) return 1;
    return 0;
}