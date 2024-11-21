typedef struct error{
    char* code;
    char* msg;
} Error;

extern const Error ERR_LEX_USE;
extern const Error ERR_LEX_NOT_TPP;
extern const Error ERR_LEX_FILE_NOT_EXISTS;
extern const Error ERR_LEX_INV_CHAR;

extern const Error ERR_SYN_USE;