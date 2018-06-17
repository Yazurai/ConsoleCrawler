#include "playerController.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "position.h"
#include "UIUtilies.h"
#include "escCodes.h"
#include "main.h"

struct position pos;
char skin = '@';
enum fgColor color = FG_WHITE;

void renderPlayer(){
    setCursorPos(pos.x, pos.y);
    setFgColor(color);
    printf("%c", skin);
}

void setPlayer(){

}

void spawnPlayer(uint8_t x, uint8_t y){
    pos.x = x;
    pos.y = y;
    renderPlayer();
}

void move(enum direction dir){
    struct position nextPos = pos;
    setCursorPos(pos.x, pos.y);  //delete the previous location
    printf(" ");
    switch (dir){
        case UP:
            nextPos.y--;
            break;
        case DOWN:
            nextPos.y++;
            break;
        case RIGHT:
            nextPos.x++;
            break;
        case LEFT:
            nextPos.x--;
            break;
    }
    if(checkWall(nextPos)){
        pos = nextPos;
    }
    renderPlayer();
}
