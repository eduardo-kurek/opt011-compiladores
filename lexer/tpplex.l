%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#ifdef WIN32
    #include <windows.h>
#endif

typedef struct error{
    char code[30];
    char message[50];
} Error;

enum LexerErrors {
    ERR_LEX_USE = 0,
    ERR_LEX_NOT_TPP = 1,
    ERR_LEX_FILE_NOT_EXISTS = 2,
    ERR_LEX_INV_CHAR = 3
};

const Error lexerErrors[] = {
    {"ERR-LEX-USE", "Uso: ./lexer file.tpp"},
    {"ERR-LEX-NOT-TPP", "Não é um arquivo .tpp"},
    {"ERR-LEX-FILE-NOT-EXISTS", "Arquivo .tpp não existe"},
    {"ERR-LEX-INV-CHAR", "Caractere inválido"}
};

bool check_key = false;

void yyerror(const Error* errorList, int errorCode, bool kill);
void yyprint(char* s);

%}

DIGITO [0-9]
LETRA [a-zA-ZáÁãÃàÀéÉíÍóÓõÕç]
ID [a-zA-ZáÁãÃàÀéÉíÍóÓõÕ][a-zA-ZáÁãÃàÀéÉíÍóÓõÕ0-9_]*

%option case-sensitive

%%


\{([^{}]|\n)*\} { /* IGNORA COMENTÁRIOS */ }


\+ { yyprint("MAIS"); }
- { yyprint("MENOS"); }
\* { yyprint("VEZES"); }
\/ { yyprint("DIVIDE"); }
\: { yyprint("DOIS_PONTOS"); }
, { yyprint("VIRGULA"); }
\< { yyprint("MENOR"); }
> { yyprint("MAIOR"); }
= { yyprint("IGUAL"); }
\<> { yyprint("DIFERENTE"); }
\<= { yyprint("MENOR_IGUAL"); }
>= { yyprint("MAIOR_IGUAL"); }
&& { yyprint("E"); }
"||" { yyprint("OU"); }
! { yyprint("NAO"); }
\( { yyprint("ABRE_PARENTESE"); }
\) { yyprint("FECHA_PARENTESE"); }
\[ { yyprint("ABRE_COLCHETE"); }
\] { yyprint("FECHA_COLCHETE"); }
se { yyprint("SE"); }
então { yyprint("ENTAO"); }
senão { yyprint("SENAO"); }
fim { yyprint("FIM"); }
repita { yyprint("REPITA"); }
até { yyprint("ATE"); }
:= { yyprint("ATRIBUICAO"); }
leia { yyprint("LEIA"); }
escreva { yyprint("ESCREVA"); }
retorna { yyprint("RETORNA"); }
inteiro { yyprint("INTEIRO"); }
flutuante { yyprint("FLUTUANTE"); }
[0-9]+ { yyprint("NUM_INTEIRO"); }
[-]?[0-9]+(\.([0-9]+)?) { yyprint("NUM_PONTO_FLUTUANTE"); }
(([-\+]?)([1-9])\.([0-9])+[eE]([-\+]?)([0-9]+)) { yyprint("NUM_NOTACAO_CIENTIFICA"); }
{ID} { yyprint("ID"); }

[ \t] { /* IGNORA ESPAÇOS EM BRANCO */ }
\n+ { yylineno++; }
.|ç { yyerror(lexerErrors, ERR_LEX_INV_CHAR, false); }

%%

void yyprint(char* s) {
    if(check_key)
        printf("%s\n", s);
    else
        printf("LexToken(%s,'%s',%d,%d)\n", s, yytext, yylineno, yyleng);
}

void yyerror(const Error* errorList, int errorCode, bool kill) {
    if(check_key)
        printf("%s\n", errorList[errorCode].code);
    else
        printf("%s\n", errorList[errorCode].message);

    if(kill) exit(1);
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

    if(fileIdx == -1) yyerror(lexerErrors, ERR_LEX_USE, true);
    if(!hasTppExtension(argv[fileIdx])) yyerror(lexerErrors, ERR_LEX_NOT_TPP, true);
    
    return fileIdx;
}

void adjustConsole() {
    #ifdef WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void openFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if(file == NULL) yyerror(lexerErrors, ERR_LEX_FILE_NOT_EXISTS, true);
    yyin = file;
}

int main(int argc, char* argv[]) {
    adjustConsole();
    int fileIdx = handleArguments(argc, argv);
    openFile(argv[fileIdx]);
    
    yylex();
    
    if (yyin) {
        fclose(yyin);
    }
    
    return 0;
}