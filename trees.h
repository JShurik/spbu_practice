#pragma once

typedef struct tree_node {
	int data;
	struct tree_node* left;
	struct tree_node* right;
} tnode;

void tree_print(tnode* tree);
void tree_free(tnode** tree);
void add_node(tnode** tree, int node);
tnode* tree_sort(const char* str);

typedef struct sb_tree {
	int a;
	int b;
	struct sb_tree* left;
	struct sb_tree* right;
} sbt;