#include "global.h"

#define OSH_OPT "|><&"
#define OSH_TOK_DELIM " \n\r\t\a|><&"

#define OPT_NONE 0
#define OPT_PIPE 1
#define OPT_TOFILE 2
#define OPT_FROMFILE 3

// Get tokens from string with delim char in delims string
// Ex. "abc xyz" -> tokens = "abc", ""
char** getTokens(char* dstStr) {
    if (dstStr == NULL)
        return NULL;
    
    if (OSH_OPT == NULL)
        return NULL;

    size_t buffSize = TOK_BUFFSIZE;
    size_t currentPos = 0;
    char** tokens = malloc(buffSize * sizeof(char*));  

    size_t startToken = 0;

    for (size_t i = 0; i <= strlen(dstStr); i++) {
        // dstStr[i] in OSH_TOK_DELIM -> get token
        // '\0': in string -> it is string terminate, so not put in OSH_TOK_DELIM
        if (dstStr[i] == '\0' || isContain(dstStr[i], OSH_TOK_DELIM)) {
            char* token;

            // Copy string from startToken to position of char delim (i)
            // and insert to tokens
            size_t len = i - startToken;
            if (len != 0) {
                token = malloc(len + 1);
                memcpy(token, dstStr + startToken, len);
                token[len] = '\0';
                tokens[currentPos] = token;
                currentPos++;
            }

            // If currentChar in OPT -> insert token OPT to tokens
            if (isContain(dstStr[i], OSH_OPT)) {
                token = malloc(2);
                token[0] = dstStr[i];
                token[1] = '\0';
                
                tokens[currentPos] = token;
                currentPos++;
            }

            startToken = i + 1;
        }

        // Increase size of array tokens if it full
        if (currentPos + 1 >= TOK_BUFFSIZE) {
            buffSize += TOK_BUFFSIZE;
            tokens = realloc(tokens, buffSize);
        }
    }
    tokens[currentPos] = NULL;

    return tokens;
}

// Parse args (include opt) to args1 & args2 (for pipe & <>)
// element of args1 and args2 pointer to args, so not free them double
int parseOptCommand(char** args, char** argsParsedOne, char** argsParsedTwo) {
    if (args == NULL)
        return OPT_NONE;

    size_t posOpt = 0;  
    size_t typeOpt = OPT_NONE;
    size_t i = 0;

    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            typeOpt = OPT_PIPE;
            posOpt = i;
        } else if (strcmp(args[i], ">") == 0) {
            typeOpt = OPT_TOFILE;
            posOpt = i;
        } else if (strcmp(args[i], "<") == 0) {
            typeOpt = OPT_FROMFILE;
            posOpt = i;
        }
    }

    memset(argsParsedOne, 0, 100);
    memset(argsParsedTwo, 0, 100);

    size_t j = 0;
    for (size_t i = 0; args[i] != NULL; i++) {
        if (i < posOpt) {
            argsParsedOne[i] = args[i];
        } else if (i > posOpt) {
            argsParsedTwo[j] = args[i];
            j++;
        }
    }

    return typeOpt;
}