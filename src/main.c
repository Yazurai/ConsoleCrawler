#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "UI/escCodes.h"
#include "position.h"
#include "playerController.h"
#include "setupUI.h"
#include "Enemy/enemy.h"
#include "objects.h"
#include "environment.h"

enum objects environment[25][80];
struct enemy enemies[20];
bool shouldStop = false;

int main(int argc, char **argv) {
    setInputMode();   //start the input
    srand(time(0));   // set random seed
    printf("%c[=3h", ESCAPE); //set the canvas to 25x80

    //Read in the environment info: walls
    FILE *wallsFile;
    char input[25][82];
    char *filename;
    if(argc > 1){
        filename = argv[0];
    } else {
        filename = "environment.txt";
    }
    wallsFile = fopen(filename, "r");
    if(wallsFile == NULL){
        printf("No environment file!");
        return 1;
    }
    for (int i = 0; i < 25; ++i) {
        fgets(input[i], 100, wallsFile);
    }
    fclose(wallsFile);

    //setup walls
    decodeInput(input);

    //setup player
    spawnPlayer(3,3);

    //setup treasures
    setupTreasure();

    //setup enemies
    for (int j = 0; j < 1; ++j) {
        bool goodPos = false;
        struct position startPos = {0, 0};
        while(!goodPos){
            startPos.x = (rand() % 80) + 1;
            startPos.y = (rand() % 25) + 1;
            if(startPos.x > 5 || startPos.y > 5){
                goodPos = true;
            }
            if(!checkEnvironment(startPos, EMPTY)){
                goodPos = false;
            }
        }
        newEnemy(&enemies[j], startPos, "X");
    }
    pthread_t threads[2];

    pthread_create(&threads[1], NULL, inputThread, NULL);
    pthread_create(&threads[0], NULL, updateEnemyThread, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
}


