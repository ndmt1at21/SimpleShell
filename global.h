#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h> // for open creat

#define TOK_BUFFSIZE 64

// Print array string. Just for debuggging
void print(char** arrStr) {
    for (size_t i = 0; arrStr[i] != NULL; i++) {
        printf("%s\n", arrStr[i]);
    }
}

void freeStr(char* str) {
    if (str != NULL) {
        free(str);
    }
}

void freeArrStr(char** arrStr) {
    if (arrStr != NULL) {
        for (size_t i = 0; arrStr[i] != NULL; i++) {
            freeStr(arrStr[i]);
        }
        free(arrStr);
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
// Return:
// 1 if char in str
// otherwise 0
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

// Getline from stream (file, stdin) to string, delim auto '\n'
// Return: string input from stream, null if nothing to read
// or not get char delim
char* readline(FILE* stream) {
    char* str = NULL;
    size_t buffSize = 0;

    if (getline(&str, &buffSize, stream) == -1)
        return NULL;
    
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

// Return: size of arr string (number of string in arr)
size_t getSizeArrStr(char** arrStr) {
    if (arrStr == NULL)
        return 0;

    size_t i = 0;
    while (true) {
        if (arrStr[i] == NULL) {
            return i;
        }
        i++;
    }
}

#endif