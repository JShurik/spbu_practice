#pragma once
typedef struct node {
	int val;
	node* next;
} node;

typedef struct list {
	node* head;
} list;

typedef struct graph {
	int n;
	list* adj_list;
} graph;

//graph* graph_init(int n);
void add_edge(graph** g, int a, int b);
void del_edge(graph**g, int a, int b);
void graph_print(graph* g);
void graph_free(graph* g);
