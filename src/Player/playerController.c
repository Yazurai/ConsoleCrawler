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

uint8_t burning = 0;
bool shield = false;
int8_t health = 100;
struct position pos;
char skin = '@';
enum fgColor color = FG_WHITE;

void renderPlayer(void) {
    setCursorPos(pos.x, pos.y);
    if (shield) {
        setBgColor(BG_CYAN);
    } else {
        if (burning > 0) {
            setBgColor(BG_RED);
        } else {
            setBgColor(BG_BLACK);
        }
    }

    setFgColor(color);
    printf("%c", skin);
    setBgColor(BG_BLACK);

    setCursorPos(84, 4);
    printf("           ");
    setFgColor(FG_RED);
    setBgColor(BG_BLACK);
    setCursorPos(84, 4);
    printf("HEALTH: %i", health);

    setCursorPos(84, 6);
    setFgColor(FG_CYAN);
    printf("SHIELD STATUS: ");
    printf(shield ? "ON " : "OFF");

    setCursorPos(84, 8);
    printf("                  ");
    setCursorPos(84, 8);
    setFgColor(FG_WHITE);
    printf("TREASURES LEFT: %d", treasureCount);

    if (burning > 0) {
        setCursorPos(84, 10);
        setBgColor(BG_RED);
        setFgColor(FG_WHITE);
        printf("BURNING!");
        setBgColor(BG_BLACK);
    } else {
        setCursorPos(84, 10);
        printf("        ");
    }
}

void spawnPlayer(uint8_t x, uint8_t y) {
    pos.x = x;
    pos.y = y;
    renderPlayer();
}

void burn(void) {
    if (checkEnvironment(pos, LAVA) && burning != 4) {
        burning = 4;
    }
    if (burning > 0) {
        health -= 5;
        burning--;
        renderPlayer();
    }
}

void move(enum direction dir) {
    struct position nextPos = pos;
    setCursorPos(pos.x, pos.y);  //set the previous location
    if (checkEnvironment(pos, LAVA)) {
        setBgColor(BG_RED);
        setFgColor(FG_BLACK);
        printf("#");
        setBgColor(BG_BLACK);
        setFgColor(FG_WHITE);
    } else {
        if (checkEnvironment(pos, SHIELD)) {
            setFgColor(FG_CYAN);
            printf("■");
            setFgColor(FG_WHITE);
        } else {
            if (checkEnvironment(pos, HEALTHPACK)) {
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
    if (!checkEnvironment(nextPos, WALL)) {
        pos = nextPos;
    }
    if (!checkEnemy(pos)) {
        if (!shield) {
            health -= 10;
            if (health == 0) {
                setCursorPos(5, 26);
                printf("__   _____  _   _ _ ___ ___   ___  ___   _   ___  _");
                setCursorPos(5, 27);
                printf("\\ \\ / / _ \\| | | ( ) _ \\ __| |   \\| __| /_\\ |   \\| |");
                setCursorPos(5, 28);
                printf(" \\ V / (_) | |_| |/|   / _|  | |) | _| / _ \\| |) |_|");
                setCursorPos(5, 29);
                printf("  |_| \\___/ \\___/  |_|_\\___| |___/|___/_/ \\_\\___/(_)");
            }
        } else {
            shield = false;
        }
    }
    if (checkEnvironment(pos, HEALTHPACK)) {
        if (health < 100) {
            health += 10;
            health = (health > 100) ? 100 : health;
            environment[pos.y - 1][pos.x - 1] = EMPTY;
        }
    }
    if (checkEnvironment(pos, SHIELD)) {
        if (!shield) {
            shield = true;
            environment[pos.y - 1][pos.x - 1] = EMPTY;
        }
    }
    if (checkEnvironment(pos, TREASURE)) {
        environment[pos.y - 1][pos.x - 1] = EMPTY;
        treasureCount--;
        if (treasureCount == 0) {
            spawnPortal();
        }
    }
    if (checkEnvironment(pos, LAVA)) {
        if (!shield) {
            burning = 4;
        } else {
            shield = false;
        }
    }
    if (checkEnvironment(pos, PORTAL)) {
        setCursorPos(5, 26);
        printf(" __   _____  _   _ ___   _____  __      _____  _  _ _ ");
        setCursorPos(5, 27);
        printf(" \\ \\ / / _ \\| | | ( ) \\ / / __| \\ \\    / / _ \\| \\| | |");
        setCursorPos(5, 28);
        printf("  \\ V / (_) | |_| |/ \\ V /| _|   \\ \\/\\/ / (_) | .` |_|");
        setCursorPos(5, 29);
        printf("   |_| \\___/ \\___/    \\_/ |___|   \\_/\\_/ \\___/|_|\\_(_)");
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
