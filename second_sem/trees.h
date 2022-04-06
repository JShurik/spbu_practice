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
void tree_to_array(tnode *tree, int* arr, int *id);

typedef struct sb_tree {
	int a;
	int b;
	struct sb_tree* left;
	struct sb_tree* right;
} sbt;

typedef struct sb_fraction {
	int up_left_a;
	int up_left_b;
	int up_right_a;
	int up_right_b;
} sbf;

sbt* get_stern_brocot_tree(int n);
sbt* get_stern_brocot_subtree(int depth, sbf f);
void sb_number(double r, sbt* tree);