#ifndef UNTITLED_SWITCH_H
#define UNTITLED_SWITCH_H

typedef struct tickBox *tickBoxPtr;

struct screenPos getPos(struct tickBox *ptr);
void setPos(struct tickBox *ptr, struct screenPos pos);

char *getLabel(struct tickBox *ptr);
bool getTicked(struct tickBox *ptr);

void newTickBoxDefault(struct tickBox *ptr);
void newTickBox(struct tickBox *ptr, uint8_t x, uint8_t y, char *label, bool baseState);

void render(struct tickBox *ptr, int color);

void flip(struct tickBox *ptr);
void focusChange(struct tickBox *ptr, bool isFocus);

#endif //UNTITLED_SWITCH_H
