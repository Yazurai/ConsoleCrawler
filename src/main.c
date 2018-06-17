#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include "UI/escCodes.h"
#include "UIUtilies.h"
#include "position.h"
#include "playerController.h"
#include "setupUI.h"

char walls[30][100];
bool shouldStop = false;

void renderWalls(void) {
    setBgColor(BG_BLACK);
    for (int i = 0; i <= 25; ++i) {
        for (int j = 0; j <= 80; ++j) {
            setCursorPos(j + 1, i + 1);
            if (walls[i][j] == 'X') {
                printf("O");
            }
        }
    }
}

bool checkWall(struct position pos){
    if(walls[pos.y - 1][pos.x - 1] == 'X'){
        return false;
    } else {
        return true;
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

    //setup walls
    renderWalls();

    //setup player
    spawnPlayer(2,2);

    //start the input
    char c;
    set_input_mode();

    while(!shouldStop){
        c = getchar();
        switch (c){
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
        }
    }

}


