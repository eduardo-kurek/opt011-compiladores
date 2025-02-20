# Variáveis
LEXER = lexer.l
PARSER = parser.y
LEXER_C = lex.yy.c
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h
SRCS = arvore_abstrata.c code_gen.c errors.c func_table.c main.c semantica.c tree.c var_table.c $(LEXER_C) $(PARSER_C)
OBJS = $(SRCS:.c=.o)
EXEC = ../gen
LLVM_VERSION = 18
LLVM_PATH = /usr/lib/llvm-$(LLVM_VERSION)
CFLAGS = -g -I$(LLVM_PATH)/include
LDFLAGS = -L$(LLVM_PATH)/lib -lfl -lLLVM

# Regra padrão
all: $(EXEC)

# Regra para o executável
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Regra para os arquivos objeto
%.o: %.c $(PARSER_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para gerar o analisador léxico
$(LEXER_C): $(LEXER) $(PARSER_H)
	flex $(LEXER)

# Regra para gerar o analisador sintático
$(PARSER_C) $(PARSER_H): $(PARSER)
	bison -d -t $(PARSER)

# Limpeza
clean:
	rm -f $(OBJS) $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXEC)