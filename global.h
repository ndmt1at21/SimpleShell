#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define OSH_TOK_BUFFSIZE 64
#define OSH_SPACES " \t\r\n"

char* readline() {
    char* str = NULL;
    size_t buffSize = 0;

    getline(&str, &buffSize, stdin);
    
    //remove \n when user hit enter
    if (strlen(str) > 0) {
        str[strlen(str) - 1] = '\0';
    }

    return str;
}

bool isSpace(char ch) {
    if (ch == ' ') {
        return true;
    }
    return false;
}

bool isContain(char ch, char* str) {
    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ch)
            return true;
    }

    return false;
}

//remove one more space in string
//ex. "abc  xyz   " -> "abc xyz "
void stripExtraSpace(char* dstStr) {
    if (dstStr == NULL)
        return;
        
    if (strlen(dstStr) == 1 && isContain(*dstStr, OSH_SPACES)) {
        *dstStr = '\0';
        return;
    }

    size_t len = strlen(dstStr);
    size_t j = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isContain(dstStr[i], OSH_SPACES) || 
            (i > 0 && !isContain(dstStr[i - 1], OSH_SPACES))) 
        {
            dstStr[j++] = dstStr[i];
        }
    }
    if (dstStr[j - 1] == ' ')
        j--;

    dstStr[j] = '\0';
}


