#include "global.h"
#define OSH_TOK_DELIM " \n\r\t\a|><"
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
    char str[] = "\a    Nguyen \n\r\r\t Duc Minh\t\t\t\t\tTri  ";
    stripExtraSpace(str, OSH_SPACES);
    printf("%s", str);
    char** a = getTokens(str, OSH_TOK_DELIM);
    print(a);
}