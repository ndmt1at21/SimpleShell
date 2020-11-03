#ifndef _HISTORY_H
#define _HISTORY_H_

#include "global.h"

#define DEFAULT_HISTFILESIZE 64;
#define DEFAULT_HISTSIZE 0;

// value default just for init
static size_t historyCurrentSize = DEFAULT_HISTSIZE;
static size_t historyBuffSize = DEFAULT_HISTFILESIZE;
static char** historyList = NULL;

// Get directory of bash file: profile, history
// nameFile: /bchx.txt
char* getDirBashFile(char* nameFile) {
    if (nameFile == NULL) {
        return NULL;
    }

    char* home = getenv("HOME");
    size_t lenDirFile = strlen(home) + strlen(nameFile);
    char* dirFile = malloc(lenDirFile + 1);

    memcpy(dirFile, home, strlen(home));
    memcpy(dirFile + strlen(home), nameFile, strlen(nameFile));
    dirFile[lenDirFile] = '\0';

    return dirFile;
}

void initHistory() {
    // Read histSize and histFileSize from osh_profile
    FILE* profile = fopen(getDirBashFile("/.osh_profile"), "r");
    if (profile != NULL) {
        fscanf(profile, "%zu\n%zu", &historyCurrentSize, &historyBuffSize);
    }

    // Allocate 1 arr to contain history
    historyList = malloc(historyBuffSize * sizeof(char*));

    // Read history from histFile
    FILE* histFile = fopen(getDirBashFile("/.osh_history"), "r");
    if (histFile == NULL) {
        historyCurrentSize = 0;
        return;
    }

    char* history;
    size_t buffSize = 0;
    size_t i = 0;

    while (i <= historyBuffSize) {
        history = readline(histFile);
        if (history == NULL)
            break;

        historyList[i] = history;
        i++;
    }
    historyCurrentSize = i >= historyBuffSize ? historyBuffSize : i;
    
    fclose(histFile);
}

void addHistory(char* newHistory) {
    if (newHistory == NULL)
        return;

    char* cpyHistory = malloc(strlen(newHistory) + 1);
    strcpy(cpyHistory, newHistory);

    if (historyCurrentSize >= historyBuffSize) {
        // shift left history
        // hisSize - 1 safe (hisSize >= 1)
        for (size_t i = 0; i < historyCurrentSize - 1; i++) {
            historyList[i] = historyList[i + 1];
        }
        freeStr(historyList[historyCurrentSize - 1]);
        historyList[historyCurrentSize - 1] = cpyHistory;
    } 
    else {
        historyList[historyCurrentSize] = cpyHistory;
        historyCurrentSize++;
    }
}

void printHistory() {
    for (size_t i = 0; i < historyCurrentSize; i++) {
        printf("%zu\t%s\n", i + 1, historyList[i]);
    }
}

void updateHistoryFile() {
    // Update profile
    FILE* profile = fopen(getDirBashFile("/.osh_profile"), "w");
    if (profile == NULL)
        return;

    fprintf(profile, "%zu\n%zu", historyCurrentSize, historyBuffSize);
    fclose(profile);

    // Update history file
    FILE* histFile = fopen(getDirBashFile("/.osh_history"), "w");
    if (histFile == NULL)
        return;

    for (size_t i = 0; i < historyCurrentSize; i++) {
        fprintf(histFile, "%s\n", historyList[i]);
    }
    fclose(histFile);
}

void clearHistory() {
    for (size_t i = 0; i < historyCurrentSize; i++) {
        freeStr(historyList[i]);
    }
    historyCurrentSize = 0;
}

void freeHistory() {
    freeArrStr(historyList);
}

#endif