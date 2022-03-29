#include <iostream>
#include "trees.h"

void tree_print(tnode* tree) {
	if (tree != NULL) {
		tree_print(tree->left);
		//std::cout << tree->data << " ";
		printf("%i ", tree->data);
		tree_print(tree->right);
	}
	return;
}

void tree_free(tnode** tree) {
	if (tree) {
		tree_free(&(*tree)->right);
		tree_free(&(*tree)->left);
		free(*tree);
	}
}

void add_node(tnode** tree, int node) {
	if (*tree == NULL) {
		*tree = (tnode*)malloc(sizeof(tnode));
		(*tree)->data = node;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
	else {
		if (node > (*tree)->data) {
			add_node(&((*tree)->right), node);
		}
		else {
			add_node(&((*tree)->left), node);
		}
	}
}

tnode* tree_sort(const char* str) {
	tnode* result = NULL;
	char* s = (char*)str;
	while (*s != '\n') {
		int num = strtol(s, &s, 10);
		add_node(&result, num);
	}
	return result;
}