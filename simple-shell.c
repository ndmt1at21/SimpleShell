#include "global.h"
#include "parse.h"
#include "exec.h"
#include "built-in.h"

#define OSH_SPACES " \t\r\n\a"

char* handleInput() {
    return readline(stdin);
}   

void oshLoop() {
    bool isRunning = true;
    char cwd[1024];

    // init history
    initHistory();

    while (isRunning) {
        getcwd(cwd, 1024);

        // Program sign
        printf("%s osh>", cwd);
        
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
        
        // exit
        if (strcmp(args[0], "exit") == 0) {
            isRunning = false;
            freeStr(inputStr);
            freeArrStr(args);
            continue;
        }

        // exec builtin (if args have keyword in builtin string)
        if (execBuiltin(args) == 1) {
            freeStr(inputStr);
            freeArrStr(args);
            continue;
        }
            
        //exec
        bool wait = isBackground(args);
        if (wait) {
            freeStr(args[getSizeArrStr(args) - 1]);
            args[getSizeArrStr(args) - 1] = NULL;
        }

        char* args1[100];
        char* args2[100];
        int typeExec = parseOptCommand(args, args1, args2);
  
        pid_t pid = fork();
        switch (pid) {
            case -1:
                perror("fork failed");
                exit(EXIT_FAILURE);

            case 0:
                //child
                switch (typeExec) {
                    case OPT_PIPE:
                        childPipe(args1, args2);
                        break;
                    case OPT_FROMFILE:
                        childFromFile(args1, args2);
                        break;
                    case OPT_TOFILE:
                        childToFile(args1, args2);
                        break;
                    default:
                        childNormal(args);
                        break;
                }
                exit(EXIT_FAILURE);
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