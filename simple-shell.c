#include "global.h"
#include "parse.h"
#include "exec.h"

#define OSH_SPACES " \t\r\n\a"

char* handleInput() {
    return readline();
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
        
        // parse 
        stripExtraSpace(inputStr, OSH_SPACES);
        char** args = getTokens(inputStr);
        
        // exec builtin
        execBuilin(args);

        //exec
        int typeExec = getTypeExec(args);
        switch (typeExec) {

        }

        // Free memory
        free(inputStr);
        freeArrStr(args);
    }

    freeHistory();
}

int main() {
    oshLoop();
}