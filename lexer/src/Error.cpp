#include "Error.h"
#include <iostream>

namespace Error{

    void Error::printCode() const{
        std::cout << this->cod << std::endl;
    }

    void Error::printMessage() const{
        std::cout << this->message << std::endl;
    }

    const Error* ERR_LEX_USE = new Error(
        "ERR-LEX-USE", "Uso: ./lex -k arquivo.tpp"
    );

    const Error* ERR_LEX_NOT_TPP = new Error(
        "ERR-LEX-NOT-TPP", "Arquivo não é um .tpp"
    );

    const Error* ERR_LEX_FILE_NOT_EXISTS = new Error(
        "ERR-LEX-FILE-NOT-EXISTS", "Tpp não existe"
    );

    const Error* ERR_LEX_INV_CHAR = new Error(
        "ERR-LEX-INV-CHAR", "Caractere inválido"
    );
}