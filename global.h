#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TOK_BUFFSIZE 64

// Print array string. Just for debuggging
void print(char** arrStr) {
    for (size_t i = 0; arrStr[i] != NULL; i++) {
        printf("%s\n", arrStr[i]);
    }
}


// Check char is space?
bool isSpace(char ch) {
    if (ch == ' ') {
        return true;
    }
    return false;
}

// Check char contain in string?
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

// Getline from stdin to string, delim auto '\n'
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

//remove one more space in string
//ex. "abc  xyz   " -> "abc xyz "
void stripExtraSpace(char* dstStr, char* spaceChars) {
    if (dstStr == NULL) {
        return;
    }
        
    if (strlen(dstStr) == 1 && isContain(*dstStr, spaceChars)) {
        *dstStr = '\0';
        return;
    }

    size_t len = strlen(dstStr);
    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        if (!isContain(dstStr[i], spaceChars) || 
            (i > 0 && !isContain(dstStr[i - 1], spaceChars))) 
        {
            dstStr[j++] = dstStr[i];
        }
    }
    if (isContain(dstStr[j - 1], spaceChars)) {
        j--;
    }

    dstStr[j] = '\0';
}

// Get tokens from string with delim char in delims string
// Ex. "abc xyz" -> tokens = "abc", "xyz"
char** getTokens(char* dstStr, char* delims) {
    if (dstStr == NULL)
        return NULL;
    
    if (delims == NULL)
        return NULL;
    
    size_t buffSize = TOK_BUFFSIZE;
    size_t currentPos = 0;
    char** tokens = malloc(buffSize * sizeof(char*));
    char* token;

    token = strtok(dstStr, delims);

    while (token != NULL) {
        tokens[currentPos] = token;
        currentPos++;

        // if current size >= maxSize alloc before -> realloc, increase maxsize
        if (currentPos >= buffSize) {
            buffSize += TOK_BUFFSIZE;
            tokens = realloc(tokens, buffSize * sizeof(char*));
        }

        token = strtok(NULL, delims);
    }
    tokens[currentPos] = NULL;
    
    return tokens;
}

