# Sobre
O parser ou analisador sintático é uma etapa de compilação de uma linguagem que consiste em verificar a gramática dos tokens. Utilizei as ferramentas Flex e Bison para realizar a análise sintática.

# Dependencias
Para compilar o parser, é necessário ter as ferramentas abaixo instaladas:
* gcc;
* Makefile;
* flex;
* bison;

# Compilação
Para compilar, execute o comando `make`. O parser será gerado na raiz do projeto. Para utilizar, use o comando `./parser file.tpp [-k]`.