#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "UI/escCodes.h"

char walls[30][100];

void renderWalls(void) {
    printf("%c[%dm", ESCAPE, BG_BLACK);
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j <= 80; ++j) {
            printf("%c[%d;%dH", ESCAPE, i, j);
            if (walls[i][j] != ' ') {
                printf("O");
            }
        }
    }
}

void main(int argc, char **argv) {
    printf("%c[=3h", ESCAPE); //set the canvas to 25x80

    //Read in the environment info: walls
    FILE *wallsFile;
    wallsFile = fopen(argv[1], "r");
    for (int i = 0; i < 25; ++i) {
        fgets(walls[i], 100, wallsFile);
    }

    renderWalls();
    getchar();
}


