#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <time.h>
#include <pthread.h>
#include "UI/escCodes.h"
#include "UIUtilies.h"
#include "position.h"
#include "playerController.h"
#include "setupUI.h"
#include "Enemy/enemy.h"
#include "objects.h"
#include "List/list.h"

struct list *environment[25][80];
char walls[25][82];
struct enemy enemies[20];
bool shouldStop = false;
pthread_t threads[2];

void initEnv(void){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            environment[i][j] = initList();
        }
    }
}

void renderWalls(void) {
    setBgColor(BG_BLACK);
    for (uint8_t i = 0; i <= 25; ++i) {
        for (uint8_t j = 0; j <= 80; ++j) {
            setCursorPos(j + 1, i + 1);
            if (walls[i][j] == 'X') {
                //add(environment[i][j], WALL);
                printf("O");
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
    if(walls[pos.y - 1][pos.x - 1] == 'X'){
        return false;
    } else {
        return true;
    }
}

void main(int argc, char **argv) {
    set_input_mode();   //start the input
    srand(time(NULL));   // set random seed
    printf("%c[=3h", ESCAPE); //set the canvas to 25x80

    //Read in the environment info: walls
    FILE *wallsFile;
    wallsFile = fopen(argv[1], "r");
    for (int i = 0; i < 25; ++i) {
        fgets(walls[i], 100, wallsFile);
    }

    fclose(wallsFile);

    //setup walls
    renderWalls();

    //setup player
    spawnPlayer(2,2);

    //setup enemies
    for (int j = 0; j < 20; ++j) {
        bool goodPos = false;
        struct position startPos = {0, 0};
        while(!goodPos){
            startPos.x = (rand() % 80) + 1;
            startPos.y = (rand() % 25) + 1;
            if(startPos.x > 5 || startPos.y > 5){
                goodPos = true;
            }
            if(!checkWall(startPos)){
                goodPos = false;
            }
        }
        newEnemy(&enemies[j], startPos, 'X');
    }

    pthread_create(&threads[1], NULL, inputThread, NULL);
    pthread_create(&threads[0], NULL, updateEnemyThread, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
}


