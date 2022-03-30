#include <iostream>
#include "tree.h"

void tree_print(tnode* tree) {
	if (tree != NULL) {
		tree_print(tree->left);
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


sbt* get_stern_brocot_subtree(int depth, sbf f) {
	if (depth == 0)
		return NULL;
	else {
		sbt* result = (sbt*)malloc(sizeof(sbt));
		result->a = f.up_left_a + f.up_right_a;
		result->b = f.up_left_b + f.up_right_b;

		sbf sub_left = f;
		sub_left.up_right_a = result->a;
		sub_left.up_right_b = result->b;
		result->left = get_stern_brocot_subtree(depth - 1, sub_left);

		sbf sub_right = f;
		sub_right.up_left_a = result->a;
		sub_right.up_left_b = result->b;
		result->right = get_stern_brocot_subtree(depth - 1, sub_right);

		return result;
	}
}

sbt* get_stern_brocot_tree(int n) {
	sbf subtree = { 0, 1, 1, 0 };
	sbt* result = get_stern_brocot_subtree(n, subtree);
	return result;
}

void sb_number(double r, sbt* tree) {
	if (tree->left == NULL) {
		printf("\n %i / %i ~ %lf", tree->a, tree->b, (double)((double)tree->a/(double)tree->b));
		return;
	}
	else {
		double num = (double)tree->a / (double)tree->b;
		if (num > r) {
			printf("L");
			sb_number(r, tree->left);
		}
		else if (num < r) {
			printf("R");
			sb_number(r, tree->right);
		}
		else
			return;
	}
}