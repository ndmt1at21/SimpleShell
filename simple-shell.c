#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

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
    char str[] = "    Nguyen \n\r\r\t Duc Minh   \t\t\t\t\t  Tri  ";
    stripExtraSpace(str);

    printf("%s", str);
}