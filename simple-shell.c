#include "global.h"
#include "parse.h"
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
    char str[] = "ls | input.txt";
    stripExtraSpace(str, OSH_SPACES);
    char** a = getTokens(str);
    print(a);
}