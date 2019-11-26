#include <UI/UIUtilies.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Enemy/enemy.h"
#include "GameUtilities/environment.h"
#include "GameUtilities/objects.h"
#include "main.h"

uint8_t treasureCount = 10;

void decodeInput(char input[25][82]) {
    for (uint8_t y = 0; y <= 25; ++y) {
        for (uint8_t x = 0; x <= 80; ++x) {
            position pos;
            pos.x = x + 1;
            pos.y = y + 1;
            switch (input[y][x]){
                case 'X':
                    environment[y][x] = WALL;
                    print(pos, FG_WHITE, BG_BLACK, "O");
                    break;
                case 'H':
                    environment[y][x] = HEALTHPACK;
                    print(pos, FG_GREEN, BG_BLACK, "+");
                    break;
                case 'S':
                    environment[y][x] = SHIELD;
                    print(pos, FG_CYAN, BG_BLACK, "■");
                    break;
                case 'L':
                    environment[y][x] = LAVA;
                    print(pos, FG_BLACK, BG_RED, "#");
                    break;
            }
        }
    }
}

void setupTreasure(void){
    for (int i = 0; i < 10; ++i) {
        struct position spawnPos;
        bool validPos = false;
        while(!validPos){
            spawnPos.x = rand() % 80 + 1;
            spawnPos.y = rand() % 25 + 1;
            if(checkEnvironment(spawnPos, EMPTY)){
                validPos = true;
            }
        }
        environment[spawnPos.y - 1][spawnPos.x - 1] = TREASURE;
        print(spawnPos, FG_YELLOW, BG_BLACK, "Ж");
    }
}

void spawnPortal(void){
    struct position spawnPos;
    bool validPos = false;
    while(!validPos){
        spawnPos.x = rand() % 80;
        spawnPos.y = rand() % 25;
        if(checkEnvironment(spawnPos, EMPTY)){
            validPos = true;
        }
    }
    environment[spawnPos.y - 1][spawnPos.x - 1] = PORTAL;
    print(spawnPos, FG_MAGENTA, BG_BLACK, "#");

}

bool checkEnemy(struct position pos){
    for (int i = 0; i < 20; ++i) {
        if(enemies[i].pos.x == pos.x && enemies[i].pos.y == pos.y){
            return false;
        }
    }
    return true;
}

bool checkEnvironment(struct position pos, enum objects obj){
    if(environment[pos.y - 1][pos.x - 1] == obj){
        return true;
    } else {
        return false;
    }
}