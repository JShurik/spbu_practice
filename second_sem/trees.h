#pragma once

typedef struct tree_node {
	int data;
	tnode* left;
	tnode* right;
} tnode;

void tree_print(tnode *tree);
void tree_free(tnode** tree);
void add_node(tnode** tree, int node);
tnode* tree_sort(const char* str);
