#ifndef _EXEC_H_
#define _EXEC_H_

#include "global.h"

bool isBackground(char** args) {
    if (args == NULL) {
        return false;
    }

    size_t prevPos = 0;
    for (size_t i = 0; args[i] != NULL; i++) {
        prevPos = i;
    }

    if (strcmp(args[prevPos], "&") == 0) {
        return true;
    }

    return false;
}

void childNormal(char** args) {
    printf("abc");
    if (execvp(args[0], args) == -1) {
        perror("execute failed\n");
        exit(EXIT_FAILURE);
    }
}

void childFromFile(char** args1, char** dir) {
    //write code in here
}

void childToFile(char** args1, char** dir) {
    //write code in here
}

void childPipe(char** argsIn, char** argsOut) {
    int fd[2];
    pid_t p1, p2;

    if (pipe(fd) < 0) {
        perror("pipe could not be initialized\n");
        exit(EXIT_FAILURE);
    }

    p1 = fork();
    if (p1 < 0) {
        perror("fork failed\n");
        exit(EXIT_FAILURE);
    }

    // child 1
    if (p1 == 0) {
        // only use write end
       
        dup2(fd[1], STDOUT_FILENO);
         close(fd[0]);
        close(fd[1]);

        childNormal(argsIn);
        exit(EXIT_FAILURE);
    }

    // child 2
    p2 = fork();
    if (p2 < 0) {
        perror("fork failed\n");
        exit(EXIT_FAILURE);
    } 
    
    if (p2 == 0) {
        // only need read end
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        childNormal(argsOut);
         exit(EXIT_FAILURE);
    } 

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

void parent(pid_t child_pid, bool wait) {
    int status;

    if (wait == 0) {
        waitpid(child_pid, &status, 0);
    } else {
        waitpid(child_pid, &status, WUNTRACED);

        if (WIFEXITED(status)) {
            printf("[%d] is finished and exited with status %d\n",child_pid,status);
        }
    }
}

#endif