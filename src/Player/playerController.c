#include "playerController.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "position.h"
#include "UIUtilies.h"
#include "escCodes.h"
#include "main.h"

#define TIME_LIMIT 0.5

struct position pos;
char skin = '@';
enum fgColor color = FG_WHITE;

void renderPlayer() {
    setCursorPos(pos.x, pos.y);
    setFgColor(color);
    printf("%c", skin);
}

void spawnPlayer(uint8_t x, uint8_t y) {
    pos.x = x;
    pos.y = y;
    renderPlayer();
}

void move(enum direction dir) {
    struct position nextPos = pos;
    setCursorPos(pos.x, pos.y);  //delete the previous location
    printf(" ");
    switch (dir) {
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
    if (checkWall(nextPos)) {
        pos = nextPos;
    }
    renderPlayer();
}

void *inputThread(void *arg) {
    char c;

    while (!shouldStop) {
        c = getchar();
        switch (c) {
            case 'w':
                move(UP);
                break;
            case 'a':
                move(LEFT);
                break;
            case 's':
                move(DOWN);
                break;
            case 'd':
                move(RIGHT);
                break;
            case ESCAPE:
                shouldStop = true;
                break;
            default:
                break;
        }
    }
    return NULL;
}
