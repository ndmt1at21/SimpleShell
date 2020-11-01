#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "build-in.h"


#define OPT_NONE 0
#define OPT_PIPE 1
#define OPT_AMPERSAND 2
#define OPT_TOFILE 3
#define OPT_FROMFILE 4

bool isBackground(char** args) {
    if (args == NULL) {
        return false;
    }

    size_t prevPos = 0;
    for (size_t i = 0; args[i] != NULL; i++) {
        prevPos = i;
    }

    if (args[prevPos] == "&") {
        return true;
    }

    return false;
}

int getTypeExec(char** args) {
    if (args == NULL) {
        return false;
    }

    for (size_t i = 0; args[i] != NULL; i++) {
        if (args[i] == "|") {
            return OPT_PIPE;
        } else if (args[i] == ">") {
            return OPT_TOFILE;
        } else if (args[i] == "<") {
            return OPT_FROMFILE;
        }
    }

    return OPT_NONE;
}

void childNormal(char** args) {
    //write code in here
}

void childFromFile(char** args) {
    //write code in here
}

void childToFile(char** args) {
    //write code in here
}

void childPipe(char** args) {
    //write code in here
}

void parent(char** args) {
    if (isBackground(args)) {
        //waitpid() 
        //write code in here
    }
}