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
    if (pos.x < 0) {
        ptr->pos.x = 0;
    } else if (pos.x > 25) {
        ptr->pos.x = 25;
    } else {
        ptr->pos.x = pos.x;
    }

    if (pos.y < 0) {
        ptr->pos.y = 0;
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
void newTickBoxDefault(struct tickBox *ptr) {
    struct tickBox tb;
    tb.pos.x = 1;
    tb.pos.y = 1;
    strcpy(tb.label, "");
    tb.ticked = false;
    ptr = &tb;
}

void newTickBox(struct tickBox *ptr, uint8_t x, uint8_t y, char *label, bool baseState) {
    struct tickBox tb;
    tb.pos.x = x;
    tb.pos.y = y;
    strcpy(tb.label, label);
    tb.ticked = baseState;
    ptr = &tb;
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
    printf("%c[%dm", ESCAPE, BG_BLACK);
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
    render(ptr, BG_BLUE);
}
void FocusChange(struct tickBox *ptr, bool isFocus) {
    if (isFocus) {
        render(ptr, BG_BLUE);
    } else {
        render(ptr, BG_BLACK);
    }
}

