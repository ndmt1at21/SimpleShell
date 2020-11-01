#include "global.h"
#include "parse.h"
#include "build-in.h"

#define OSH_SPACES " \t\r\n\a"

void handleInput() {
    char* line = readline();
    printf("%s", line);
    printf("%zu", strlen(line));

    free(line);
}   

void oshLoop() {
    while (1) {
        handleInput();
    }
}

int main() {
    char* args[] = {"cd", "desktop"};
    execBuilin(args);
}