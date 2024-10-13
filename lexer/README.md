# Sobre
* O código do analisador léxico foi escrito em C através da ferramente **Flex**. O código para testes foi escrito em python e está no arquivo `tpplex_test.py`

# Dependências
* Para compilar o código do lexer é necessario ter o [Flex](https://www.geeksforgeeks.org/flex-fast-lexical-analyzer-generator/) instalado, juntamente com a biblioteca `libfl` (é para ela vir junto com o Flex). Make e GCC também são necessários. Para os testes é necessário ter o `python` juntamente com a biblioteca `pytest` instalada.

# Compilação
* Para compilar ocódigo do lexer, basta executar executar o comando `make` e o executável `tpplex` sera gerado. Você consegue analisar o arquivo `lex.yy.c` criado pelo Flex.

# Execução
* Uma vez que o executável do lexer está gerado, basta executar informando um arquivo .tpp como parâmetro e uma flag opcional (-k) para exibir apenas os tokens.

# Testes
* Os testes percorrem todos os arquivos presentes na pasta `tests/` e compara a saída gerada pelo lexer com o arquivo de saída esperada. Para executar todos os testes, basta executar o comando `pytest` na raiz do projeto, ele automaticamente executará todas as funções contidas no arquivo `*_test.py`. Lembrando que antes de realizar os testes, o lexer deve ser compilado.
