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
    bgColor bgC = BG_BLACK;
    if (shield) {
        bgC = BG_CYAN;
    } else if (burning > 0) {
        bgC = BG_RED;
    }

    print(pos, color, bgC, &skin);
    position textPos = {.x = 84, .y = 4};

    textPos = (position) {.x = 84, .y = 4};
    print(textPos, FG_WHITE, BG_BLACK, "                    ");
    textPos = (position) {.x = 84, .y = 6};
    print(textPos, FG_WHITE, BG_BLACK, "                    ");
    textPos = (position) {.x = 84, .y = 8};
    print(textPos, FG_WHITE, BG_BLACK, "                    ");

    textPos = (position) {.x = 84, .y = 4};
    print(textPos, FG_RED, BG_BLACK, "HEALTH: ");
    char uiText[5];
    sprintf(uiText, "%d", health);
    textPos = (position) {.x = 92, .y = 4};
    print(textPos, FG_RED, BG_BLACK, uiText);

    textPos = (position) {.x = 84, .y = 6};
    print(textPos, FG_CYAN, BG_BLACK, "SHIELD STATUS: ");
    textPos = (position) {.x = 99, .y = 6};
    print(textPos, FG_CYAN, BG_BLACK, shield ? "ON " : "OFF");

    textPos = (position) {.x = 84, .y = 8};
    print(textPos, FG_WHITE, BG_BLACK, "TREASURES LEFT: ");
    textPos = (position) {.x = 100, .y = 8};
    sprintf(uiText, "%d", treasureCount);
    print(textPos, FG_WHITE, BG_BLACK, uiText);

    if (burning > 0) {
        textPos = (position) {.x = 84, .y = 10};
        print(textPos, FG_WHITE, BG_RED, "BURNING!");
    } else {
        textPos = (position) {.x = 84, .y = 10};
        print(textPos, FG_WHITE, BG_BLACK, "        ");
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
    position previousPos = pos;
    if (checkEnvironment(pos, LAVA)) {
        print(previousPos, FG_BLACK, BG_RED, "#");
    } else if (checkEnvironment(pos, SHIELD)) {
        print(previousPos, FG_CYAN, BG_BLACK, "■");
    } else if (checkEnvironment(pos, HEALTHPACK)) {
        print(previousPos, FG_GREEN, BG_BLACK, "¤");
    } else if (!checkEnemy(pos)) {
        print(previousPos, FG_RED, BG_BLACK, "X");
    } else {
        print(previousPos, FG_BLACK, BG_BLACK, " ");
    }

    position nextPos = pos;
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
    if (!
            checkEnvironment(nextPos, WALL
            )) {
        pos = nextPos;
    }
    if (!
            checkEnemy(pos)
            ) {
        if (!shield) {
            health -= 10;
            if (health == 0) {
                position textPos = {15, 14};
                print(textPos, FG_WHITE, BG_BLACK, "__   _____  _   _ _ ___ ___   ___  ___   _   ___  _");
                textPos = (position) {15, 15};
                print(textPos, FG_WHITE, BG_BLACK, "\\ \\ / / _ \\| | | ( ) _ \\ __| |   \\| __| /_\\ |   \\| |");
                textPos = (position) {15, 16};;
                print(textPos, FG_WHITE, BG_BLACK, " \\ V / (_) | |_| |/|   / _|  | |) | _| / _ \\| |) |_|");
                textPos = (position) {15, 17};
                print(textPos, FG_WHITE, BG_BLACK, "  |_| \\___/ \\___/  |_|_\\___| |___/|___/_/ \\_\\___/(_)");
            }
        } else {
            shield = false;
        }
    }
    if (
            checkEnvironment(pos, HEALTHPACK
            )) {
        if (health < 100) {
            health += 10;
            health = (health > 100) ? 100 : health;
            environment[pos.y - 1][pos.x - 1] =
                    EMPTY;
        }
    }
    if (
            checkEnvironment(pos, SHIELD
            )) {
        if (!shield) {
            shield = true;
            environment[pos.y - 1][pos.x - 1] =
                    EMPTY;
        }
    }
    if (
            checkEnvironment(pos, TREASURE
            )) {
        environment[pos.y - 1][pos.x - 1] =
                EMPTY;
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
        position textPos = {15, 14};
        print(textPos, FG_WHITE, BG_BLACK, " __   _____  _   _ ___   _____  __      _____  _  _ _ ");
        textPos = (position){15, 15};
        print(textPos, FG_WHITE, BG_BLACK, " \\ \\ / / _ \\| | | ( ) \\ / / __| \\ \\    / / _ \\| \\| | |");
        textPos = (position){15, 16};;
        print(textPos, FG_WHITE, BG_BLACK, "  \\ V / (_) | |_| |/ \\ V /| _|   \\ \\/\\/ / (_) | .` |_|");
        textPos = (position){15, 17};
        print(textPos, FG_WHITE, BG_BLACK, "   |_| \\___/ \\___/    \\_/ |___|   \\_/\\_/ \\___/|_|\\_(_)");
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

