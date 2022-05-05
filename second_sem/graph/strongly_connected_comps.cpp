#include <iostream>
#include "graph.h"

void dfs1(graph* g, int current, int* n) {
	n++;
	int next = g->adj_list[current]->ver;
}

int** strongly_connected_comps(graph* g) {
	int** result = (int**)malloc(sizeof(int)*g->n);
	int* out = (int*)malloc(g->n);
	int* color = (int*)calloc(g->n, sizeof(int));
	int n = 0;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] != 0) {
			dfs1(g, 0, &n);
		}
	}

}