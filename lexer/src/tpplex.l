%{
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#ifdef WIN32
    #include <windows.h>
#endif

#include "Error.h"

FlexLexer* lex = nullptr;

int column = 1;
bool check_key = false;
void yyerror(const Error::Error* err);
void yyfatal_error(const Error::Error* err);
void yyprint(const char* s);
void adjustConsole();
int handleArguments(int argc, char* argv[]);
void redirectStdin(const char* fileName);

%}

DIGITO [0-9]
LETRA [a-zA-ZáÁãÃàÀéÉíÍóÓõÕç]
ID [a-zA-ZáÁãÃàÀéÉíÍóÓõÕ][a-zA-ZáÁãÃàÀéÉíÍóÓõÕ0-9_]*

%option case-sensitive
%option noyywrap
%option yylineno
%option c++
%%

\{([^{}]|\n)*\} /* IGNORA COMENTÁRIOS */ ;

\+ yyprint("MAIS");
- yyprint("MENOS");
\* yyprint("VEZES");
\/ yyprint("DIVIDE");
\: yyprint("DOIS_PONTOS");
, yyprint("VIRGULA");
\< yyprint("MENOR");
> yyprint("MAIOR");
= yyprint("IGUAL");
\<> yyprint("DIFERENTE");
\<= yyprint("MENOR_IGUAL");
>= yyprint("MAIOR_IGUAL");
&& yyprint("E");
"||" yyprint("OU");
! yyprint("NAO");
\( yyprint("ABRE_PARENTESE");
\) yyprint("FECHA_PARENTESE");
\[ yyprint("ABRE_COLCHETE");
\] yyprint("FECHA_COLCHETE");
se yyprint("SE");
então yyprint("ENTAO");
senão yyprint("SENAO");
fim yyprint("FIM");
repita yyprint("REPITA");
até yyprint("ATE");
:= yyprint("ATRIBUICAO");
leia yyprint("LEIA");
escreva yyprint("ESCREVA");
retorna yyprint("RETORNA");
inteiro yyprint("INTEIRO");
flutuante yyprint("FLUTUANTE");
[0-9]+ yyprint("NUM_INTEIRO");
[-]?[0-9]+(\.([0-9]+)?) yyprint("NUM_PONTO_FLUTUANTE");
(([-\+]?)([1-9])\.([0-9])+[eE]([-\+]?)([0-9]+)) yyprint("NUM_NOTACAO_CIENTIFICA");
{ID} yyprint("ID");

[ \t] /* IGNORA ESPAÇOS EM BRANCO */ column++;
\r\n|\n  /* IGNORA QUEBRAS DE LINHA */ column = 1;
.|ç yyerror(Error::ERR_LEX_INV_CHAR);

%%

void yyprint(const char* s) {
    if(check_key)
        printf("%s\n", s);
    else
        printf("LexToken(%s,'%s',%d,%d)\n", s, lex->YYText(), lex->lineno(), column);
    column += lex->YYLeng();
}

void yyerror(const Error::Error* err){
    if(check_key) err->printCode();
    else err->printMessage();
}

void yyfatal_error(const Error::Error* err) {
    if(check_key) err->printCode();
    else err->printMessage();
    exit(1);
}

int main(int argc, char* argv[]) {
    adjustConsole();
    int fileIdx = handleArguments(argc, argv);
    redirectStdin(argv[fileIdx]);

    lex = new yyFlexLexer();
    lex->yylex();

    return 0;
}


bool stringHasPoint(const char* str){
    if(strstr(str, ".") == NULL) return false;
    return true;
}

bool hasTppExtension(const char* str){
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

bool stringIsK(const char* str){
    return !strcmp(str, "-k");
}


int handleArguments(int argc, char* argv[]) {
    int fileIdx = -1;
    bool check_tpp = false;
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

    if(fileIdx == -1) yyfatal_error(Error::ERR_LEX_USE);
    if(!hasTppExtension(argv[fileIdx])) yyfatal_error(Error::ERR_LEX_NOT_TPP);
    
    return fileIdx;
}

void adjustConsole() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void redirectStdin(const char* fileName) {
    std::ifstream file(fileName);
    if(!file.good()) yyfatal_error(Error::ERR_LEX_FILE_NOT_EXISTS); 
    freopen(fileName, "r", stdin);
}