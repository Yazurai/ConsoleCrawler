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
//VARIABLES
//-------------------------
struct screenPos pos;

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
struct tickBox *newTickBox() {
    struct tickBox tb;
    tb.pos.x = 1;
    tb.pos.y = 1;
    strcpy(tb.label, "");
    tb.ticked = false;
}

void Switch(int x, int y, char *label, bool baseState) {
    struct tickBox tb;
    tb.pos.x = x;
    tb.pos.y = y;
    strcpy(tb.label, label);
    tb.ticked = baseState;
}

//-------------------------
//Cursor movements
//-------------------------
void MoveCursorToStart(struct tickBox *ptr) {
    printf("%c[%d;%dH", ESCAPE, ptr->pos.x, ptr->pos.y);
}
void MoveCursorToEnd(struct tickBox *ptr) {
    printf("%c[%d;%dH", ESCAPE, ptr->pos.x, ptr->pos.y + (uint32_t)strlen(ptr->label) + 5);
}

//-------------------------
//Rendering
//-------------------------
void Render(struct tickBox *ptr, int color) {
    char printed[25] = "";
    strcat(printed , ptr->label);
    if (ptr->ticked) {
        strcat(printed ,"[X]");
    } else {
        strcat(printed ,"[ ]");
    }
    MoveCursorToEnd(ptr);
    printf("%c[%dm", ESCAPE, B:BLACK);
    printf("%c[1K", ESCAPE);
    printf("%c[%dm", ESCAPE, color);
    MoveCursorToStart(ptr);
    printf(printed);
}

//-------------------------
//State Changes
//-------------------------
void Flip(struct tickBox *ptr) {
    ptr->ticked = ptr->ticked ? false : true;
    Render(ptr, BLUE);
}
void FocusChange(struct tickBox *ptr, bool isFocus) {
    if (isFocus) {
        Render(ptr, BLUE);
    } else {
        Render(ptr, BLACK);
    }
}

