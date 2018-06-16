#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "tickBox.h"
#include "UIUtilies.h"
#include "escCodes.h"

struct tickBox{
    struct screenPos pos;
    char label[21];
    bool ticked;
};

//-------------------------
//VARIABLE FUNCTIONS
//-------------------------
struct screenPos getPos(struct tickBox *ptr) {
    return ptr->pos;
}

void setPos(struct tickBox *ptr, struct screenPos pos) {
    if (pos.x < 1) {
        ptr->pos.x = 1;
    } else if (pos.x > 24) {
        ptr->pos.x = 24;
    } else {
        ptr->pos.x = pos.x;
    }

    if (pos.y < 1) {
        ptr->pos.y = 1;
    } else if (pos.y > 80) {
        ptr->pos.y = 80;
    } else {
        ptr->pos.y = pos.y;
    }
}

char *getLabel(struct tickBox *ptr) {
    return ptr->label;
}

bool getTicked(struct tickBox *ptr) {
    return ptr->ticked;
}

//-------------------------
//FUNCTIONS
//-------------------------
struct tickBox *newTickBoxDefault() {
    struct tickBox tb;
    tb.pos.x = 1;
    tb.pos.y = 1;
    strcpy(tb.label, "");
    tb.ticked = false;
    return &tb;
}

struct tickBox *newTickBox(uint8_t x, uint8_t y, char *label, bool baseState) {
    struct tickBox tb;
    tb.pos.x = x;
    tb.pos.y = y;
    strcpy(tb.label, label);
    tb.ticked = baseState;
    return &tb;
}

//-------------------------
//Cursor movements
//-------------------------
void moveCursorToStart(struct tickBox *ptr) {
    printf("%c[%d;%dH", ESCAPE, ptr->pos.x, ptr->pos.y);
}
void moveCursorToEnd(struct tickBox *ptr) {
    printf("%c[%d;%dH", ESCAPE, ptr->pos.x, ptr->pos.y + (uint32_t)strlen(ptr->label) + 5);
}

//-------------------------
//Rendering
//-------------------------
void render(struct tickBox *ptr, int color) {
    char printed[25] = "";
    strcat(printed , ptr->label);
    if (ptr->ticked) {
        strcat(printed ,"[X]");
    } else {
        strcat(printed ,"[ ]");
    }
    moveCursorToEnd(ptr);
    printf("%c[%dm", ESCAPE, BLACK);
    printf("%c[1K", ESCAPE);
    printf("%c[%dm", ESCAPE, color);
    moveCursorToStart(ptr);
    printf(printed);
}

//-------------------------
//State Changes
//-------------------------
void flip(struct tickBox *ptr) {
    ptr->ticked = ptr->ticked ? false : true;
    render(ptr, BLUE);
}
void FocusChange(struct tickBox *ptr, bool isFocus) {
    if (isFocus) {
        render(ptr, BLUE);
    } else {
        render(ptr, BLACK);
    }
}

