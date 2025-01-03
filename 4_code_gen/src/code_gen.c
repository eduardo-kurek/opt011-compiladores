#include "code_gen.h"
#include "types.h"
#include "var_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>

LLVMModuleRef module;
LLVMContextRef context;
LLVMBuilderRef builder;
char scope[256];

void print_llvm_type(LLVMTypeRef t) {
    LLVMTypeKind typeKind = LLVMGetTypeKind(t);

    switch (typeKind) {
        case LLVMVoidTypeKind:
            printf("Tipo: void\n");
            break;
        case LLVMFloatTypeKind:
            printf("Tipo: double (64-bit floating point)\n");
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
    return LLVMBuildLoad2(builder, expectedType, entry->ref, node->label);
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
        vt_insere_variavel_alocada(node->ch[i]->label, scope, var, t);
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
        return LLVMBuildFAdd(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "addtmp"); 
    else
        return LLVMBuildFSub(builder, PROCESSA_NODE_EXPECTED(left, LLVMFloatType()), PROCESSA_NODE_EXPECTED(right, LLVMFloatType()), "subtmp");
    return LLVMBuildFPToSI(builder, result, expectedType, "convtmp");
}

Value gerar_retorna(Node* node, Type expectedType){
    return LLVMBuildRet(builder, PROCESSA_NODE_EXPECTED(node->ch[0], expectedType));
}

Value processa_node(Node* node, Type expectedType){
    switch (node->type){
        case NT_RETORNA: return gerar_retorna(node, expectedType);
        case NT_EXPRESSAO_ADITIVA: return expressao_aditiva(node, expectedType);
        case NT_EXPRESSAO_MULTIPLICATIVA: return expressao_multiplicativa(node, expectedType);
        case NT_DECLARACAO_VARIAVEIS: return declaracao_variaveis(node);
        case NT_ATRIBUICAO: return atribuicao(node);
        case NT_NUM_INTEIRO: return num(node, expectedType);
        case NT_NUM_PONTO_FLUTUANTE: return num(node, expectedType);
        case NT_VAR: return var(node, expectedType);
        
        default: printf("\033[0;35mProcessamento '%s' não implementado\033[0m\n", node_type_to_string(node));
    }

    return NULL;
}

void gerar_acao(Node* node, Type expectedType){
    int i = 0;
    if(node->child_count == 2)
        gerar_acao(node->ch[i++], expectedType);
    PROCESSA_NODE_EXPECTED(node->ch[i], expectedType);
}

ParamList gerar_lista_parametros(Node* node){
    ParamList list = malloc(sizeof(struct ParamList));
    list->count = 0;
    list->types = NULL;
    return list;
}

void gerar_cabecalho(Node* node, Type returnType){
    char* funcName = node->ch[0]->label;
    if(strcmp(funcName, "principal") == 0)
        funcName = "main";
    strcpy(scope, funcName);
    ParamList funcParam = gerar_lista_parametros(node->ch[1]);
    Type funcType = LLVMFunctionType(returnType, funcParam->types, funcParam->count, 0);
    Value func = LLVMAddFunction(module, funcName, funcType);

    // Prepara a função para receber instruções
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    // Gera o corpo da função
    gerar_acao(node->ch[2], returnType);

    //Value ref = LLVMBuildAlloca(builder, LLVMDoubleType(), "ref");

    free(funcParam);
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
}