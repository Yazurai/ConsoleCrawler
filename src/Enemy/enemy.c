#include "enemy.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "playerController.h"
#include "position.h"
#include "UIUtilies.h"
#include "main.h"
#include "environment.h"

void newEnemy(struct enemy *ptr, struct position pos, char skin){
    ptr->skin = skin;
    ptr->pos = pos;
    renderEnemy(ptr);
}

void renderEnemy(struct enemy *ptr){
    setCursorPos(ptr->pos.x, ptr->pos.y);
    setFgColor(FG_RED);
    printf("%c", ptr->skin);
    setFgColor(FG_WHITE);
}

void moveEnemy(struct enemy *ptr, enum direction dir){
    struct position nextPos = ptr->pos;
    setCursorPos(ptr->pos.x, ptr->pos.y);  //set the previous location
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
    if(checkEnvironment(nextPos, EMPTY)){
        ptr->pos = nextPos;
    }
    renderEnemy(ptr);
}

void *updateEnemyThread(void *arg){
    while(!shouldStop) {
        printf("\n");
        time_t prevTime = clock();
        uint64_t msec = 0;

        do {
            clock_t difference = clock() - prevTime;
            msec = difference * 1000 / CLOCKS_PER_SEC;
        } while (msec < 1000);

        burn();

        for (int i = 0; i < 20; ++i) {
            uint8_t random = rand() % 4;
            switch (random){
                case 0:
                    moveEnemy(&enemies[i], UP);
                    break;
                case 1:
                    moveEnemy(&enemies[i], DOWN);
                    break;
                case 2:
                    moveEnemy(&enemies[i], LEFT);
                    break;
                case 3:
                    moveEnemy(&enemies[i], RIGHT);
                    break;
                default:
                    break;
            }
        }
        setCursorPos(10, 26);
    }
    return NULL;
}