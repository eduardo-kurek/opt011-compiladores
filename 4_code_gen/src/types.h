#ifndef TYPES_H
#define TYPES_H

#include <llvm-c/Core.h>

typedef enum node_type node_type;

typedef enum primitive_type {
    T_INTEIRO, T_FLUTUANTE, T_VAZIO, T_CIENTIFICO
} primitive_type;

typedef enum var_dimension {
    SCALAR, VECTOR, MATRIX
} var_dimension;

typedef struct param param;
typedef struct func_table func_table;
typedef struct func_table_entry ft_entry;

typedef struct var_table var_table;
typedef struct var_table_entry vt_entry;

typedef LLVMValueRef Value;
typedef LLVMTypeRef Type;

typedef struct ParamList{
    Type* types;
    int count;
}* ParamList;

#endif