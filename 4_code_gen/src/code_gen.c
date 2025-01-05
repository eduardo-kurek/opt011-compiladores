#include "code_gen.h"
#include "types.h"
#include "var_table.h"
#include "func_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>

LLVMModuleRef module;
LLVMContextRef context;
LLVMBuilderRef builder;
Value function; // Função atual para geração dos blocos (se, repita...)
char scope[256];

void print_llvm_type(LLVMTypeRef t) {
    LLVMTypeKind typeKind = LLVMGetTypeKind(t);

    switch (typeKind) {
        case LLVMVoidTypeKind:
            printf("Tipo: void\n");
            break;
        case LLVMFloatTypeKind:
            printf("Tipo: float\n");
            break;
        case LLVMIntegerTypeKind:
            printf("Tipo: inteiro\n");
            break;
        default:
            printf("Tipo desconhecido\n");
            break;
    }
}

Value processa_node(Node* node, Type expectedType);
void gerar_acao(Node* node, Type expectedType);

#define PROCESSA_NODE(node) processa_node(node, LLVMVoidType())
#define PROCESSA_NODE_EXPECTED(node, expectedType) processa_node(node, expectedType)

Type tipo(node_type type){
    if(type == NT_INTEIRO) return LLVMInt32Type();
    else if(NT_FLUTUANTE) return LLVMFloatType();
    else return LLVMVoidType();
}

Value inteiro(){ return LLVMConstPointerNull(LLVMPointerType(LLVMInt32Type(), 0)); }

Value num(Node* node, Type expectedType){
    LLVMTypeKind kind = LLVMGetTypeKind(expectedType);
    switch(kind){
        case LLVMFloatTypeKind:
            return LLVMConstReal(LLVMFloatType(), atof(node->label));
        case LLVMIntegerTypeKind:
            return LLVMConstInt(LLVMInt32Type(), atoi(node->label), 0);
        default:
            printf("Tipo inesperado\n");
            print_llvm_type(expectedType);
            return NULL;
    }
}

Value var(Node* node, Type expectedType){
    vt_entry* entry = vt_obter_variavel_alocada(node->label);
    Type type = entry->type == T_INTEIRO ? LLVMInt32Type() : LLVMFloatType();
    Value value;

    if(entry->isParam)
        value = entry->ref;
    else
        value = LLVMBuildLoad2(builder, type, entry->ref, node->label);
        
    LLVMTypeKind originalKind = LLVMGetTypeKind(type), expectedKind = LLVMGetTypeKind(expectedType);
    if(originalKind == expectedKind) return value;
    if(originalKind == LLVMFloatTypeKind && expectedKind == LLVMIntegerTypeKind)
        return LLVMBuildFPToSI(builder, value, expectedType, "float2int");
    else if(originalKind == LLVMIntegerTypeKind && expectedKind == LLVMFloatTypeKind)
        return LLVMBuildSIToFP(builder, value, expectedType, "int2float");
    return NULL;
}

Value atribuicao(Node* node){
    vt_entry* entry = vt_obter_variavel_alocada(node->ch[0]->label);
    Value var = entry->ref;
    Type type = entry->type == T_INTEIRO ? LLVMInt32Type() : LLVMFloatType();
    Value expr = PROCESSA_NODE_EXPECTED(node->ch[1], type);
    return LLVMBuildStore(builder, expr, var);
}

Value lista_variaveis(Node* node, Type type){
    primitive_type t;
    LLVMTypeKind kind = LLVMGetTypeKind(type);
    switch(kind){
        case LLVMFloatTypeKind:
            t = T_FLUTUANTE;
            break;
        case LLVMIntegerTypeKind:
            t = T_INTEIRO;
            break;
        default: printf("Tipo inesperado\n");
    }
    for(int i = 0; i < node->child_count; i++){
        Value var = LLVMBuildAlloca(builder, type, node->ch[i]->label);
        vt_insere_variavel_alocada(node->ch[i]->label, scope, var, t, false);
    }
    return NULL;
    // TODO tratar indice
}

Value declaracao_variaveis(Node* node){
    Type type = tipo(node->ch[0]->type);
    return lista_variaveis(node->ch[1], type);
}

Value expressao_multiplicativa(Node* node, Type expectedType){
    Node* left = node->ch[0], *right = node->ch[1];
    Value result;
    if(strcmp(node->label, "*") == 0)
        result = LLVMBuildFMul(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "multmp");
    else
        result = LLVMBuildFDiv(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "divtmp");
    return LLVMBuildFPToSI(builder, result, expectedType, "convtmp");
}

Value expressao_aditiva(Node* node, Type expectedType){
    Node* left = node->ch[0], *right = node->ch[1];
    Value result;
    if(strcmp(node->label, "+") == 0)
        result = LLVMBuildFAdd(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "addtmp"); 
    else
        result = LLVMBuildFSub(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "subtmp");
    return LLVMBuildFPToSI(builder, result, expectedType, "convtmp");
}

Value gerar_retorna(Node* node, Type expectedType){
    return LLVMBuildRet(builder, PROCESSA_NODE_EXPECTED(node->ch[0], expectedType));
}

Value se_senao(Node* node, Type expectedType){
    LLVMBasicBlockRef blocoThen = LLVMAppendBasicBlock(function, "then");
    LLVMBasicBlockRef blocoElse = LLVMAppendBasicBlock(function, "else");
    LLVMBasicBlockRef blocoEnd = LLVMAppendBasicBlock(function, "end");

    LLVMBuildCondBr(builder, PROCESSA_NODE_EXPECTED(node->ch[0], LLVMInt32Type()), blocoThen, blocoElse);

    LLVMPositionBuilderAtEnd(builder, blocoThen);
    gerar_acao(node->ch[1], expectedType); // gera o corpo do then
    LLVMBuildBr(builder, blocoEnd); // Jump para fim

    LLVMPositionBuilderAtEnd(builder, blocoElse);
    gerar_acao(node->ch[2], expectedType); // gera o corpo do else
    LLVMBuildBr(builder, blocoEnd); // Jump para fim

    LLVMPositionBuilderAtEnd(builder, blocoEnd);
}

Value se(Node* node, Type expectedType){
    LLVMBasicBlockRef blocoThen = LLVMAppendBasicBlock(function, "then");
    LLVMBasicBlockRef blocoEnd = LLVMAppendBasicBlock(function, "end");

    LLVMBuildCondBr(builder, PROCESSA_NODE_EXPECTED(node->ch[0], LLVMInt32Type()), blocoThen, blocoEnd);

    LLVMPositionBuilderAtEnd(builder, blocoThen);
    gerar_acao(node->ch[1], expectedType); // gera o corpo do then
    LLVMBuildBr(builder, blocoEnd); // Jump para fim

    LLVMPositionBuilderAtEnd(builder, blocoEnd);
}

Value expressao_simples(Node* node, Type expectedType){
    Node* left = node->ch[0], *right = node->ch[1];
    LLVMRealPredicate pred;
    if(strcmp(node->label, ">") == 0)
        pred = LLVMRealOGT;
    else if(strcmp(node->label, "<") == 0)
        pred = LLVMRealOLT;
    else if(strcmp(node->label, ">=") == 0)
        pred = LLVMRealOGE;
    else if(strcmp(node->label, "<=") == 0)
        pred = LLVMRealOLE;
    else if(strcmp(node->label, "=") == 0)
        pred = LLVMRealOEQ;
    else if(strcmp(node->label, "<>") == 0)
        pred = LLVMRealONE;
    else
        printf("Operador não implementado\n");
    return LLVMBuildFCmp(builder, pred, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "cmptmp");
}

Value expressao_logica(Node* node, Type expectedType){
    Node* left = node->ch[0], *right = node->ch[1];
    if(strcmp(node->label, "&&") == 0)
        return LLVMBuildAnd(builder, PROCESSA_NODE_EXPECTED(left, NULL), PROCESSA_NODE_EXPECTED(right, NULL), "andtmp");
    else if(strcmp(node->label, "||") == 0)
        return LLVMBuildOr(builder, PROCESSA_NODE_EXPECTED(left, NULL), PROCESSA_NODE_EXPECTED(right, NULL), "ortmp");
    return NULL;
}

Value repita(Node* node, Type expectedType){
    LLVMBasicBlockRef blocoRepita = LLVMAppendBasicBlock(function, "repita");
    LLVMBasicBlockRef blocoFim = LLVMAppendBasicBlock(function, "fim");

    LLVMBuildBr(builder, blocoRepita);

    LLVMPositionBuilderAtEnd(builder, blocoRepita);
    gerar_acao(node->ch[0], expectedType); // gera o corpo do repita
    LLVMBuildCondBr(builder, PROCESSA_NODE_EXPECTED(node->ch[1], LLVMInt32Type()), blocoRepita, blocoFim);

    LLVMPositionBuilderAtEnd(builder, blocoFim);
}

Value lista_argumentos(Node* node, Type returnType, Value* args, int* qt, Type* expectedTypes){
    int i = 0;
    if(node->child_count == 2)
        lista_argumentos(node->ch[i++], returnType, args, qt, expectedTypes);
    Node* argNode = node->ch[i];
    if(argNode->type == NT_VAZIO)
        return NULL;

    Value value = PROCESSA_NODE_EXPECTED(argNode, expectedTypes[*qt]);
    args[*qt] = value;
    *qt = *qt + 1;
    return NULL;
}

Value chamada_funcao(Node* node, Type expectedType){
    ft_entry* func = ft_get_func_llvm(node->ch[0]->label);
    if(func == NULL){
        printf("Função '%s' não declarada\n", node->ch[0]->label);
        return NULL;
    }

    Value* args = malloc(func->param_count * sizeof(Value));
    int qt = 0;
    lista_argumentos(node->ch[1], expectedType, args, &qt, func->paramTypes);
    Value result = LLVMBuildCall2(builder, func->funcType, func->func, args, qt, "calltmp");
    return result;
}

Value processa_node(Node* node, Type expectedType){
    switch (node->type){
        case NT_RETORNA: return gerar_retorna(node, expectedType);
        case NT_EXPRESSAO_ADITIVA: return expressao_aditiva(node, expectedType);
        case NT_EXPRESSAO_MULTIPLICATIVA: return expressao_multiplicativa(node, expectedType);
        case NT_EXPRESSAO_SIMPLES: return expressao_simples(node, expectedType);
        case NT_EXPRESSAO_LOGICA: return expressao_logica(node, expectedType);
        case NT_DECLARACAO_VARIAVEIS: return declaracao_variaveis(node);
        case NT_ATRIBUICAO: return atribuicao(node);
        case NT_NUM_INTEIRO: return num(node, expectedType);
        case NT_NUM_PONTO_FLUTUANTE: return num(node, expectedType);
        case NT_VAR: return var(node, expectedType);
        case NT_SE:{
            if(node->child_count == 3) return se_senao(node, expectedType);
            return se(node, expectedType);
        }
        case NT_REPITA: return repita(node, expectedType);
        case NT_CHAMADA_FUNCAO: return chamada_funcao(node, expectedType);
        case NT_VAZIO: return NULL;
        
        default: printf("\033[0;35mProcessamento '%s' não implementado\033[0m\n", node_type_to_string(node));
    }

    return NULL;
}

void gerar_acao(Node* node, Type expectedType){
    if(node->type == NT_VAZIO) return;
    int i = 0;
    if(node->child_count == 2)
        gerar_acao(node->ch[i++], expectedType);
    PROCESSA_NODE_EXPECTED(node->ch[i], expectedType);
}

void parametro(Node* node, ParamList list){
    if(node->type == NT_VAZIO) return;
    Type type = tipo(node->ch[0]->type);
    Param param = malloc(sizeof(struct Param));
    param->type = type;
    param->name = node->ch[1]->label;
    param->line = node->ch[1]->line;
    list->params = realloc(list->params, (list->count + 1) * sizeof(Param));
    list->params[list->count] = param;
    list->count++;
}

void lista_parametros(Node* node, ParamList list){
    int i = 0;
    if(node->child_count == 2)
        lista_parametros(node->ch[i++], list);
    parametro(node->ch[i], list);
}

ParamList gerar_parametros(Node* node){
    ParamList list = malloc(sizeof(struct ParamList));
    list->count = 0;
    list->params = NULL;
    lista_parametros(node, list);
    return list;
}

void gerar_cabecalho(Node* node, Type returnType){
    char* funcName = node->ch[0]->label;
    if(strcmp(funcName, "principal") == 0)
        funcName = "main";
    strcpy(scope, funcName);
    ParamList funcParam = gerar_parametros(node->ch[1]);
    Type* types = malloc(funcParam->count * sizeof(Type));
    for(int i = 0; i < funcParam->count; i++) types[i] = funcParam->params[i]->type;
    Type funcType = LLVMFunctionType(returnType, types, funcParam->count, 0);
    Value func = LLVMAddFunction(module, funcName, funcType);
    function = func; // Atualiza a função atual

    ft_insere_func_llvm(funcName, funcType, types, func, funcParam->count);

    // Prepara a função para receber instruções
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    // Salvando todos os parametros na tabela
    for(int i = 0; i < funcParam->count; i++){
        Value param = LLVMGetParam(func, i);
        vt_insere_variavel_alocada(funcParam->params[i]->name, scope, 
            param, funcParam->params[i]->type == LLVMInt32Type() ? T_INTEIRO : T_FLUTUANTE, true);
    }

    // Gera o corpo da função
    gerar_acao(node->ch[2], returnType);

    // Coloca uma instrução de retorno padrão
    LLVMTypeKind returnTypeKind = LLVMGetTypeKind(returnType);
    if(returnTypeKind == LLVMVoidTypeKind)
        LLVMBuildRetVoid(builder);
    else if(returnTypeKind == LLVMFloatTypeKind)
        LLVMBuildRet(builder, LLVMConstReal(returnType, 0.0));
    else
        LLVMBuildRet(builder, LLVMConstInt(returnType, 0, 0));

    vt_remove_todos(scope);
}

void gerar_declaracao_funcao(Node* node){
    Type returnType;
    int i = 0;
    if(node->ch[0]->type == NT_INTEIRO){ returnType = LLVMInt32Type(); i++; }
    else if(node->ch[0]->type == NT_FLUTUANTE){ returnType = LLVMFloatType(); i++; }
    else returnType = LLVMVoidType();
    gerar_cabecalho(node->ch[i], returnType);
}

void gerar_declaracao(Node* node){
    int i = 0;
    if(node->child_count == 2)
        gerar_declaracao(node->ch[i++]);

    switch(node->ch[i]->type){
        case NT_DECLARACAO_FUNCAO:
            gerar_declaracao_funcao(node->ch[i]);
            break;
        
        // TODO restantes dos casos

        default:
            printf("Declaração não implementada\n");
            break;
    }
}

void gerar_codigo(Node* root){
    vt_init();
    ft_init();
    printf("Gerando código...\n");

    context = LLVMGetGlobalContext();
    module = LLVMModuleCreateWithName("program.bc");
    builder = LLVMCreateBuilder();

    gerar_declaracao(root->ch[0]);

    if(LLVMPrintModuleToFile(module, "output.ll", NULL) != 0){
        fprintf(stderr, "Erro ao salvar o arquivo .ll.\n");
    }

    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    vt_destroy();
    ft_destroy();
}