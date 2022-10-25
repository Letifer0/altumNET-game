#include <stdio.h>
#include <stdlib.h>

#if defined (_WIN32)

void clearConsole() {
    system("cls");
}

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)

void clearConsole() {
    system("clear");
}

#elif defined (__APPLE__)

void clearConsole() {
    system("clear");
}

#endif