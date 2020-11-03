#ifndef _EXEC_H_
#define _EXEC_H_

#include "global.h"

// Check ampersand in args
// Return: true if "&"" in args, otherwise 0
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
    if (execvp(args[0], args) < 0) {
        perror("execute failed\n");
        exit(EXIT_FAILURE);
    }
}

// Exec child from file
// dir: directory file in
void childFromFile(char** args, char** dir) {
    if (dir == NULL) {
        perror("invalid directory\n");
        exit(EXIT_FAILURE);
    }

    int fd;
    fd = open(dir[0], O_RDONLY);

    if (fd == -1) {
        perror("file desciptor: cannot open\n");
        exit(EXIT_FAILURE);
    }

    dup2(fd, STDIN_FILENO);
    if (close(fd) < 0) {
        perror("file desciptor: cannot close\n");
        exit(EXIT_FAILURE);
    }

    childNormal(args);
}

void childToFile(char** args, char** dir) {
    if (dir == NULL) {
        perror("invalid directory\n");
        exit(EXIT_FAILURE);
    }
   
    int fd;
    fd = creat(dir[0], S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);

    if (fd == -1) {
        perror("file desciptor: cannot create\n");
        exit(EXIT_FAILURE);
    }

    dup2(fd, STDOUT_FILENO);
    if (close(fd) < 0) {
        perror("file desciptor: cannot close\n");
        exit(EXIT_FAILURE);
    }

    childNormal(args);
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
            printf("[%d] is finished and exited with status %d\n", child_pid, status);
        }
    }
}

#endif