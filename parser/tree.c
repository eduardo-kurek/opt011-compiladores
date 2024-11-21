#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define INITIAL_CHILD_COUNT 5

int lastId = 0;

struct node{
    int id;
    char label[256];
    struct node** children;
    int child_count;
    int child_max;
};

Node* node_create(const char* label){
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = lastId++;
    strncpy(node->label, label, sizeof(node->label) - 1);
    node->label[sizeof(node->label) - 1] = '\0';
    node->child_count = 0;
    node->child_max = INITIAL_CHILD_COUNT;

    Node** children = (Node**)malloc(sizeof(Node*) * INITIAL_CHILD_COUNT);
    node->children = children;
}

void node_adjust_children_length(Node* node){
    if(node->child_count == node->child_max){
        int new_size = node->child_max * 1.5;
        node->children = (Node**)realloc(node->children, sizeof(Node*) * new_size);
        node->child_max = new_size;
    }
}

void node_add_child(Node *parent, Node *child){
    node_adjust_children_length(parent);
    parent->children[parent->child_count++] = child;
}

void node_add_children(Node* parent, int num_children, ...) {
    va_list args;
    va_start(args, num_children);

    for (int i = 0; i < num_children; i++) {
        Node* child = va_arg(args, Node*);
        node_add_child(parent, child);
    }

    va_end(args);
}


Node* node_add_new_child(Node *parent, const char* label){
    Node* child = node_create(label);
    node_add_child(parent, child);
}

void generate_dot(Node* node, FILE* file){
    if(node == NULL) return;

    fprintf(file, "\t%d [label=\"%s\"];\n", node->id, node->label);
    for(int i = 0; i < node->child_count; i++){
        fprintf(file, "\t%d -> %d;\n", node->id, node->children[i]->id);
        generate_dot(node->children[i], file);
    }
}

void node_to_dot(Node* root, const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "digraph Tree {\n");
    fprintf(file, "    node [shape=ellipse];\n");

    if (root != NULL) {
        generate_dot(root, file);
    }

    fprintf(file, "}\n");
    fclose(file);
}

void node_print(Node* node){
    printf("Node: %d\nChild_max: %d\nChild_count: %d\nChildren:", node->id, node->child_max, node->child_count);
    for(int i = 0; i < node->child_count; i++){
        printf("\tId: %d\n", node->children[i]->id);
    }
}

Node* node_create_leaf(const char *parentLabel, const char *childLabel){
    Node* parent = node_create(parentLabel);
    Node* child = node_create(childLabel);
    node_add_child(parent, child);
    return parent;
}


