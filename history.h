#include <stdio.h>
#include <stdlib.h>

static size_t historyCurrentSize = 0;
static size_t historyBuffSize = 1;
static char** historyList = NULL;

void initHistory() {
    historyList = malloc(historyBuffSize * sizeof(char*));
}

void addHistory(char* newHistory) {
    if (newHistory == NULL)
        return;

    if (historyCurrentSize >= historyBuffSize) {
        // shift left history
        // hisSize - 1 safe (hisSize >= 1)
        for (size_t i = 0; i < historyCurrentSize - 1; i++) {
            historyList[i] = historyList[i + 1];
        }
        free(historyList[historyCurrentSize - 1]);
        historyList[historyCurrentSize - 1] = newHistory;
    } else {
        historyList[historyCurrentSize] = newHistory;
        historyCurrentSize++;
    }
    

}

void printHistory() {
    for (size_t i = 0; i < historyCurrentSize; i++) {
        printf("%zu\t%s", i, historyList[i]);
    }
}

void clearHistory() {
    for (size_t i = 0; i < historyCurrentSize; i++) {
        free(historyList[i]);
    }
    historyCurrentSize = 0;
}