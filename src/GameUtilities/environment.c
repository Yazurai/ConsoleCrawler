#include <UI/UIUtilies.h>
#include <stdbool.h>
#include <stdio.h>
#include "Enemy/enemy.h"
#include "environment.h"
#include "objects.h"
#include "main.h"

uint8_t treasureCount = 10;

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
        setCursorPos(spawnPos.x, spawnPos.y);
        setFgColor(FG_YELLOW);
        printf("Ж");
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
    setCursorPos(spawnPos.x, spawnPos.y);
    setFgColor(FG_MAGENTA);
    printf("#");
    setFgColor(FG_WHITE);
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