#pragma once
#include "list.h"

typedef struct graph {
	int n;
	list** adj_list;
} graph;

//building graph
void graph_free(graph* g);
graph* graph_init(int n);
void add_arc(graph* g, int a, int b);
void add_edge(graph* g, int a, int b);
void del_edge(graph* g, int a, int b);
void graph_print(graph* g);

//working with files
graph* graph_read(const char* input);
void graph_write(graph* g, const char* output);

//graph algorithms
int* bipart_check_bfs(graph* g);
int* bipart_check_dfs(graph* g);
void print_parts(int* color);

int* topological_sort(graph* g);
list** change_vertexes(int* order, graph* g);

int* tarjan_scc(graph* g);
int* scc(graph* g);
void printComponents(int* components);