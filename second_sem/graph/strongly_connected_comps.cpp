#include <iostream>
#include "graph.h"

const int UNVISITED = -1;

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

void dfs_tarjan(int current, graph* g, int* count, int* ids, int* lowLink, int* onStack, list* stack, int* id) {
	list_push(&stack, current);
	onStack[current] = 1;
	ids[current] = (*id)++;
	lowLink[current] = ids[current];
	list* nextVertexes = g->adj_list[current];
	while (nextVertexes) {
		int next = nextVertexes->ver;
		if (ids[next] == UNVISITED) {
			dfs_tarjan(next, g, count, ids, lowLink, onStack, stack, id);
		}
		if (onStack[next]) {
			lowLink[current] = min(lowLink[current], lowLink[next]);
		}
		nextVertexes = nextVertexes->next;
	}
	if (ids[current] == lowLink[current]) {
		while (stack) {
			int node = list_pop_up(&stack);
			onStack[node] = 0;
			lowLink[node] = ids[current];
			if (node == current)
				break;
		}
		(*count)++;
	}
	return;
}

int** tarjan_scc(graph* g) {
	int id = 0, sccCount = 0;
	int* nodeOnStack = (int*)malloc(g->n);	
	int* ids = (int*)malloc(g->n);
	int* lowLinkValues = (int*)malloc(g->n);
	for (int i = 0; i < g->n; ++i) {
		lowLinkValues[i] = 0; 
		ids[i] = UNVISITED; 
		nodeOnStack[i] = 0;
	}
	list* nodeStack = NULL;

	for (int i = 0; i < g->n; ++i) {
		if (ids[i] == UNVISITED) {
			dfs_tarjan(i, g, &sccCount, ids, lowLinkValues, nodeOnStack, nodeStack, &id);
		}
	}
	
	int** result = (int**)malloc(sizeof(int)*sccCount);
	int compNum = 0;
	for (int i = 0; i < sccCount; ++i) {
		int* vertexes = (int*)malloc(g->n);
		int counter = 0;
		for (int j = 0; j < g->n; ++j) {
			if (lowLinkValues[j] == compNum) {
				vertexes[counter] = j;
				counter++;
			}
		}
		compNum++;
		if (vertexes[0] < 0) {
			i--;
		}
		else {
			result[i] = vertexes;
		}
	}
	return result;
}


int** scc(graph* g) {
	return 0;
}
int** strongly_connected_comps(graph* g) {
	int** result = (int**)malloc(sizeof(int) * g->n);
	int* out = (int*)malloc(g->n);
	int* color = (int*)calloc(g->n, sizeof(int));
	int n = 0;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] != 0) {
			//dfs1(g, 0, &n);
		}
	}
	return 0;
}