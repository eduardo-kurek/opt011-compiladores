#include <stdarg.h>

typedef struct node Node;

Node* node_create(const char* label);
int node_get_child_count(Node* node);
Node* node_create_leaf(const char* parentLabel, const char* childLabel);
void node_add_child(Node* parent, Node* child);
void node_add_children(Node* parent, int num_children, ...);
Node* node_add_new_child(Node* parent, const char* label);
void node_to_dot(Node* root, const char* filename);
void node_print(Node* node);