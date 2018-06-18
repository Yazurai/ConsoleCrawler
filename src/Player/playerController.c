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
#include "objects.h"
#include "environment.h"

int8_t health = 100;
struct position pos;
char skin = '@';
enum fgColor color = FG_WHITE;

void renderPlayer() {
    setCursorPos(pos.x, pos.y);
    setFgColor(color);
    printf("%c", skin);
    setCursorPos(84, 4);
    printf("           ");
    setCursorPos(84, 4);
    setFgColor(FG_RED);
    printf("HEALTH: %i", health);
}

void spawnPlayer(uint8_t x, uint8_t y) {
    pos.x = x;
    pos.y = y;
    renderPlayer();
}

void move(enum direction dir) {
    struct position nextPos = pos;
    setCursorPos(pos.x, pos.y);  //set the previous location
    if(checkHealthPack(pos)){
        setFgColor(FG_GREEN);
        printf("¤");
        setFgColor(FG_WHITE);
    } else {
        if (!checkEnemy(pos)) {
            setFgColor(FG_RED);
            printf("X");
            setFgColor(FG_WHITE);
        } else {
            printf(" ");
        }
    }

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
    if (!checkEnemy(pos)){
        health -= 10;
        if(health == 0){
            setCursorPos(5, 26);
            printf("__   _____  _   _ _ ___ ___   ___  ___   _   ___  _");
            setCursorPos(5, 27);
            printf("\\ \\ / / _ \\| | | ( ) _ \\ __| |   \\| __| /_\\ |   \\| |");
            setCursorPos(5, 28);
            printf(" \\ V / (_) | |_| |/|   / _|  | |) | _| / _ \\| |) |_|");
            setCursorPos(5, 29);
            printf("  |_| \\___/ \\___/  |_|_\\___| |___/|___/_/ \\_\\___/(_)");
        }
    }
    if(checkHealthPack(pos)){
        if(health < 100){
            health += 10;
            health = (health > 100) ? 100 : health;
            environment[pos.y - 1][pos.x - 1] = EMPTY;
        }
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
