#include "global.h"
#include "parse.h"
#include "exec.h"

#define OSH_SPACES " \t\r\n\a"

char* handleInput() {
    return readline(stdin);
}   

void oshLoop() {
    bool isRunning = true;

    // init history
    initHistory();

    while (isRunning) {
        // Program sign
        printf("osh>");
        
        // user input
        char* inputStr = handleInput();
        if (strlen(inputStr) == 0)
            continue;

        // add user input to hisstory
        addHistory(inputStr);
        updateHistoryFile();

        // parse 
        stripExtraSpace(inputStr, OSH_SPACES);
        char** args = getTokens(inputStr);
        
        //check exit 
        if (strcmp(args[0], "exit") == 0)
            isRunning = false;

        // exec builtin (if args have keyword in builtin string)
        execBuiltin(args);

        //exec
        int typeExec = getTypeExec(args);
        pid_t pid = fork();

        switch (pid) {
            case -1:
                perror("fork failed");
                exit(EXIT_FAILURE);

            case 0:
                //child
                switch (typeExec) {
                    case OPT_PIPE:
                        childPipe(args);
                        break;
                    case OPT_FROMFILE:
                        childFromFile(args);
                        break;
                    case OPT_TOFILE:
                        childToFile(args);
                        break;
                    default:
                        childNormal(args);
                }
                break;

            default:
                //parent
                parent(pid, wait);
        }

        // Free memory
        freeStr(inputStr);
        freeArrStr(args);
    }

    freeHistory();
}

int main() {
    oshLoop();
}