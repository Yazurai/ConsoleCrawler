#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "UI/escCodes.h"

char walls[25][80];

void main(int argc, char **argv){
    printf("%c[=3h",ESCAPE); //set the canvas to 25x80

    //Read in the environment info: walls
    FILE *wallsFile;
    wallsFile = fopen(argv[1], "r");
    for (int i = 0; i < 25; ++i) {
        fread(walls[i], sizeof(walls[i]), 1,wallsFile);
    }
}

void renderWalls(void){
    printf("%c[%dm", ESCAPE, BLACK);
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            printf("%c[%d;%dH", ESCAPE, i + 1, j + 1);
            if(walls[i][j] != ' '){
                printf("☐");
            }
        }
    }
}

