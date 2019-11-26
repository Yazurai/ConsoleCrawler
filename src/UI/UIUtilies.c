#include "UIUtilies.h"
#include "GameUtilities/position.h"
#include <stdint.h>
#include <stdio.h>

void setCursorPosition(position pos){

    printf("%c[%d;%dH", ESCAPE, pos.y, pos.x);
}

void setFgColor(fgColor color){
    printf("%c[%dm", ESCAPE, color);
}

void setBgColor(bgColor color){
    printf("%c[%dm", ESCAPE, color);
}

void moveCursor(enum direction dir, uint8_t amount){
    printf("%c[%d%c", ESCAPE, amount, dir);
}

void resetColors(){
    setBgColor(BG_BLACK);
    setFgColor(FG_WHITE);
}

void print(position pos, fgColor fgC, bgColor bgC, char *text){
    if(text != NULL) {
        setCursorPosition(pos);
        setBgColor(bgC);
        setFgColor(fgC);
        printf("%s", text);
        resetColors();
    } else {

    }
}