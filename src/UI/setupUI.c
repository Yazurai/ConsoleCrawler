#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ABUF_INIT {NULL, 0}

//Use this variable to remember original terminal attributes.
struct termios savedAttributes;

struct abuf {
  char *b;
  int len;
};

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &savedAttributes);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &savedAttributes);
    atexit(disableRawMode);
    struct termios raw = savedAttributes;
    raw.c_iflag &= ~(IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);  
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void abAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b, ab->len + len);
    if (new == NULL) return;
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}

void setInputMode(void) {
    struct termios tattr;

    // Make sure stdin is a terminal.
    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    enableRawMode();

    //hide cursor
    struct abuf ab = ABUF_INIT;
    abAppend(&ab, "\x1b[?25l", 6);
}