#ifndef _GLOBAL_H
#define _GLOBAL_H

struct SimpleCommand {
    // Max size array args
    size_t m_nBuffSizeArgs;

    // Current size array args
    size_t m_nCurrentSizeArgs;

    // Array arguments
    char** m_arrArgs;

    SimpleCommand() : m_nBuffSizeArgs(0), m_nCurrenSizeArgs(0) {

    }

    void insertArgs(char* arg) {
        
    }
};

#endif