#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "global.h"
#include "history.h"

const char* builtinStr[] = {
    "cd",
    "!!", //history
    "help",
    NULL 
};

int builtinHistory(char** args) {
    if (args[1] == NULL) {
        printHistory();
    } else if (strcmp(args[1], "-c") == 0) {
        clearHistory();
    } else {
        perror("bad option history");
    }

    return 1;
}

int builtinCd(char** args) {
    // args[0] = "cd"
    if (args[1] == NULL) {
        perror("unknown directory");
    } else {
        if (chdir(args[1])) {
            perror("cd failed");
        }
    }

    return 1;
}

int builtinHelp() {
    printf("Nothing in here, you can do it by yourself :))");
    return 1;
}

// Func pointer built in
// args: built-in string
int (*builtinFunc[])(char**) = {
    &builtinCd,
    &builtinHistory,
    &builtinHelp
};

// Exec built in 
// Return: 
// 1 if any func built-in exec
// 0 if no built-in func exec
int execBuiltin(char** args) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(args[0], builtinStr[i]) == 0) {
            return (*builtinFunc[i])(args);
        }
    }

    return 0;
}

#endif