#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <llvm-c/Core.h>
#include <llvm-c/BitReader.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Support.h>
#include <llvm-c/BitWriter.h>

LLVMContextRef context;
LLVMModuleRef module;
LLVMBuilderRef builder;

void CreateFunction(char const* argv[]);

int main(int argc, char const *argv[]){
    context = LLVMGetGlobalContext();
    module = LLVMModuleCreateWithNameInContext("meu_modulo.bc", context);
    builder = LLVMCreateBuilderInContext(context);

    CreateFunction(argv);

    LLVMWriteBitcodeToFile(module, "meu_modulo.bc");
    return 0;
}

void CreateSumFunction(){
    LLVMTypeRef param_types[] = {LLVMInt32Type(), LLVMInt32Type()}; // Dois parâmetros do tipo i32
    LLVMTypeRef return_type = LLVMInt32Type(); // Tipo de retorno i32
    LLVMTypeRef function_type = LLVMFunctionType(return_type, param_types, 2, 0); // Função com dois parâmetros
    LLVMValueRef soma_func = LLVMAddFunction(module, "soma", function_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(soma_func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    LLVMValueRef param_a = LLVMGetParam(soma_func, 0);
    LLVMValueRef param_b = LLVMGetParam(soma_func, 1);

    LLVMValueRef sum = LLVMBuildAdd(builder, param_a, param_b, "sum");
    LLVMBuildRet(builder, sum);
}

void CreateMainFunction(const char* argv[]){
    LLVMTypeRef return_type = LLVMInt32Type(); // Tipo de retorno i32
    LLVMTypeRef function_type = LLVMFunctionType(return_type, NULL, 0, 0); // Função sem parâmetros
    LLVMValueRef main_func = LLVMAddFunction(module, "main", function_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    LLVMValueRef soma_func = LLVMGetNamedFunction(module, "soma");
    LLVMTypeRef param_types[] = {LLVMInt32TypeInContext(context), LLVMInt32TypeInContext(context)};
    LLVMTypeRef soma_func_type = LLVMFunctionType(LLVMInt32TypeInContext(context), param_types, 2, 0);

    LLVMValueRef args[] = {
        LLVMConstInt(LLVMInt32Type(), atoi(argv[1]), 0), // Primeiro argumento: 10
        LLVMConstInt(LLVMInt32Type(), atoi(argv[2]), 0)  // Segundo argumento: 20
    };

    LLVMValueRef result = LLVMBuildCall2(
        builder, soma_func_type, 
        soma_func, args, 2, "call_soma"
    );

    LLVMBuildRet(builder, result);
}

void CreateFunction(char const* argv[]){
    CreateSumFunction();
    CreateMainFunction(argv);
}
