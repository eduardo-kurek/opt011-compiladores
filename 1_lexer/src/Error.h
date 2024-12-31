#pragma once

#include <string>

namespace Error{

    class Error{

        std::string cod;
        std::string message;
        

    public: 
        Error(std::string cod, std::string message) : 
            cod(cod), message(message) {}

        virtual void printCode() const;
        virtual void printMessage() const;

    };

    extern const Error* ERR_LEX_USE;
    extern const Error* ERR_LEX_NOT_TPP;
    extern const Error* ERR_LEX_FILE_NOT_EXISTS;
    extern const Error* ERR_LEX_INV_CHAR;
}