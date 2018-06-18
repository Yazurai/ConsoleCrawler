#include <UI/UIUtilies.h>
#include <stdbool.h>
#include <stdio.h>
#include "Enemy/enemy.h"
#include "environment.h"
#include "objects.h"
#include "main.h"

void decodeInput(char input[25][82]) {
    setBgColor(BG_BLACK);
    for (uint8_t i = 0; i <= 25; ++i) {
        for (uint8_t j = 0; j <= 80; ++j) {
            setCursorPos(j + 1, i + 1);
            switch (input[i][j]){
                case 'X':
                    environment[i][j] = WALL;
                    setFgColor(FG_WHITE);
                    printf("O");
                    setFgColor(FG_WHITE);
                    break;
                case 'H':
                    environment[i][j] = HEALTHPACK;
                    setFgColor(FG_GREEN);
                    printf("¤");
                    setFgColor(FG_WHITE);
                    break;
                case 'S':
                    environment[i][j] = SHIELD;
                    setFgColor(FG_CYAN);
                    printf("■");
                    setFgColor(FG_WHITE);
                    break;
            }
        }
    }
}

bool checkEnemy(struct position pos){
    for (int i = 0; i < 20; ++i) {
        if(enemies[i].pos.x == pos.x && enemies[i].pos.y == pos.y){
            return false;
        }
    }
    return true;
}

bool checkWall(struct position pos){
    if(environment[pos.y - 1][pos.x - 1] == WALL){
        return false;
    } else {
        return true;
    }
}

bool checkHealthPack(struct position pos){
    if(environment[pos.y - 1][pos.x - 1] == HEALTHPACK){
        return true;
    } else {
        return false;
    }
}

bool checkShield(struct position pos){
    if(environment[pos.y - 1][pos.x - 1] == SHIELD){
        return true;
    } else {
        return false;
    }
}