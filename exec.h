#ifndef _EXEC_H_
#define _EXEC_H_

#include "global.h"

#define OPT_NONE 0
#define OPT_PIPE 1
#define OPT_TOFILE 2
#define OPT_FROMFILE 3

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
    execvp(args[0], args);
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

void parent(pid_t child_pid, bool wait) {
    int status;

    if (wait) {
        waitpid(child_pid, &status, WUNTRACED);

        if (WIFEXITED(status)) {
            printf("[%d] is finished and exited with status %d\n",child_pid,status);
        }
    } else {
        waitpid(child_pid, &status, 0);
    }
}

#endif