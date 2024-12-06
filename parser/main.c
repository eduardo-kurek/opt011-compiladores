#include "test.tab.h"
#include "tree.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_key = false;

extern Node* syntax_tree;
extern FILE* yyin;

void yyfatal_error(const Error* err);
bool stringHasPoint(const char* str);
bool hasTppExtension(const char* str);
bool stringIsK(const char* str);
int handleArguments(int argc, char* argv[]);
void redirectYyin(const char* fileName);

int main(int argc, char* argv[]) {
    int fileIdx = handleArguments(argc, argv);
    redirectYyin(argv[fileIdx]);

    yyin = fopen(argv[fileIdx], "r");

    do {
        yyparse();
    } while(!feof(yyin));

    node_to_dot(syntax_tree, "tree.dot");

    return 0;
}

void yyfatal_error(const Error* err){
    if(check_key)
        printf("%s\n", err->cod);
    else 
        printf("%s\n", err->msg);
    exit(1);
}

bool stringHasPoint(const char *str){
    if(strstr(str, ".") == NULL) return false;
    return true;
}

bool hasTppExtension(const char* str) {
    char buffer[256];  
    strncpy(buffer, str, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ".");
    char *last_token = NULL;

    while (token != NULL) {
        last_token = token;
        token = strtok(NULL, ".");
    }

    return (last_token != NULL && strcmp(last_token, "tpp") == 0);
}

bool stringIsK(const char* str) {
    return !strcmp(str, "-k");
}

int handleArguments(int argc, char* argv[]) {
    int fileIdx = -1;

    for(int i = 1; i < argc; i++) {
        char* arg = argv[i];

        if(stringIsK(arg)){
            check_key = true;
            continue;
        }

        if(stringHasPoint(arg)){
            fileIdx = i;
        }
    }

    if(fileIdx == -1) yyfatal_error(&ERR_SYN_USE);
    if(!hasTppExtension(argv[fileIdx])) yyfatal_error(&ERR_SYN_NOT_TPP);
    
    return fileIdx;
}

void redirectYyin(const char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL) yyfatal_error(&ERR_SYN_FILE_NOT_EXISTS);
    yyin = file;
}