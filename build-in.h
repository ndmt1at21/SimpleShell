#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "history.h"

const char* buildinStr[] = {
    "cd",
    "!!", //history
    "help",
    NULL 
};

void buildinHistory(char** args) {
    if (args[1] == "-c") {
        clearHistory();
    } else if (args[1] == NULL) {
        printHistory();
    } else {
        perror("bad option history");
    }
}

void buildinCd(char** args) {
    // args[0] = "cd"
    if (args[1] == NULL) {
        perror("unknown directory");
    } else {
        if (chdir(args[1])) {
            perror("cd failed");
        }
    }
}

void buildinHelp() {
    printf("Nothing in here, you can do it by yourself :))");
}

void (*buildinFunc[])(char**) = {
    &buildinCd,
    &buildinHistory,
    &buildinHelp
};

void execBuilin(char** args) {
    for (int i = 0; buildinStr[i] != NULL; i++) {
        if (strcmp(args[0], buildinStr[i]) == 0) {
            return (*buildinFunc[i])(args);
        }
    }
}