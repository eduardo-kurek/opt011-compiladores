#include "test.tab.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

extern Node* syntax_tree;
extern FILE* yyin;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

	do{
		yyparse();
	} while(!feof(yyin));

    node_to_dot(syntax_tree, "tree.dot");

    return 0;
}