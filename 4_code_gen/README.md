# Considerações
* Estou usando `llvm-18` para a compilação do compilador, se você tiver uma versão diferente, certifique-se de alterar no arquivo `src/Makefile` a linha `LLVM_VERSION := 18`. Você pode utilizar o comando `ls /usr/lib/ | grep llvm-` para verificar a sua versão (considerando que sua instalação esta em /usr/lib);

* Considerei que o caminho das bibliotecas llvm estão na pasta `/usr/lib/llvm-${VERSION}`, se a sua estiver em uma pasta diferente, pode alterar também no arquivo `src/Makefile`;

* Não é possiíel inicializar um array ou matriz globalmente.

* Não é possível alterar valor de parâmetros de funções diretamente, primeiro é preciso carrega-los para uma variavel local.

# Compilação
Para compilar o compilador, basta usar o comando `make`. Ferramentas necessárias para compilação:

* gcc;
* Makefile;
* flex;
* bison;
* llvm;

# Dependências de execução

* Para gerar o código objeto do arquivo LL, estou utilizando o programa `llc`, ele gera o código objeto no caminho: `/tmp/tmp_tpc_obj.o`. Verifique se você possui o `llc` com o comando `which llc`, se não, pode ser instalado com `sudo apt install llvm`;

* Para gerar o executável do código objeto, estou usando o `gcc`, ele espera que o arquivo do código objeto está no caminho `/tmp/tmp_tpc_obj.o`. Verifique se você possui o `gcc` com o comando `which gcc`, se não, pode ser instalado com `sudo apt install gcc`;