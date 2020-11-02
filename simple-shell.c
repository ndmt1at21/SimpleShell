#include "global.h"
#include "parse.h"
#include "exec.h"

#define OSH_SPACES " \t\r\n\a"

char* handleInput() {
    return readline(stdin);
}   

void oshLoop() {
    // init history
    initHistory();

    while (true) {
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
        
        // exec builtin (if args have keyword in builtin string)
        execBuilin(args);

        //exec
        pid_t pid = folk();

        switch (pid) {
            case -1:
                perror("folk failed");
                exit(EXIT_FAILURE);

            case 0:
                //child
                int typeExec = getTypeExec(args);
                switch (typeExec) {
                    case OPT_PIPE:
                        childPipe(args);
                        break;
                    case OPT_FROMFILE:
                        childFromFile();
                        break;
                    case OPT_TOFILE:
                        childToFile();
                        break;
                    default:
                        child();
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