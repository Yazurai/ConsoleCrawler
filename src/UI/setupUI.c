#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//Use this variable to remember original terminal attributes.
struct termios saved_attributes;

void resetInputMode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void setInputMode(void) {
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, &saved_attributes);
    atexit(resetInputMode);

    /* Set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 0;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);

    //hide cursor
    hidecursor();
}