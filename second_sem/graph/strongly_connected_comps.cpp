#include <iostream>
#include "graph.h"

const int UNVISITED = -1;

//tarjan scc
int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

void dfs_tarjan(int current, graph* g, int* count, int* ids, int* lowLinkValues, int* onStack, list** stack, int* id) {
	listPushUp(stack, current);
	onStack[current] = 1;
	ids[current] = (*id)++;
	lowLinkValues[current] = ids[current];
	list* nextVertexes = g->adj_list[current];
	while (nextVertexes) {
		int next = nextVertexes->ver;
		if (ids[next] == UNVISITED) {
			dfs_tarjan(next, g, count, ids, lowLinkValues, onStack, stack, id);
		}
		if (onStack[next]) {
			lowLinkValues[current] = min(lowLinkValues[current], lowLinkValues[next]);
		}
		nextVertexes = nextVertexes->next;
	}
	if (ids[current] == lowLinkValues[current]) {
		while (*stack) {
			int node = list_pop_up(stack);
			onStack[node] = 0;
			lowLinkValues[node] = ids[current];
			if (node == current)
				break;
		}
		(*count)++;
	}
	return;
}

int* tarjan_scc(graph* g) {
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
			dfs_tarjan(i, g, &sccCount, ids, lowLinkValues, nodeOnStack, &nodeStack, &id);
		}
	}
	int* result = lowLinkValues;
	//free(ids);
	//free(nodeOnStack);
	//result = (list**)realloc(result, sizeof(list)*sccCount);
	return result;
}


//classic scc
void sorting_dfs(graph* g, int current, int* color, list** orderStack) {
	color[current] = 1;
	list* nextVertexes = g->adj_list[current];
	while (nextVertexes) {
		int next = nextVertexes->ver;
		if (color[next] == UNVISITED)
			sorting_dfs(g, next, color, orderStack);
		nextVertexes = nextVertexes->next;
	}
	listPushBack(orderStack, current);
}

void dfs(graph* g, int current, int* color, list** components) {
	color[current] = 1;
	list* nextVertexes = g->adj_list[current];
	listPushUp(components, current);
	while (nextVertexes) {
		int next = nextVertexes->ver;
		if (color[next] == UNVISITED)
			dfs(g, next, color, components);
		nextVertexes = nextVertexes->next;
	}
}

int* scc(graph* g) {
	int* color = (int*)malloc(g->n);
	list* orderStack = NULL;
	int time = 0;
	for (int i = 0; i < g->n; ++i)
		color[i] = UNVISITED;
	for (int i = 0; i < g->n; i++) {
		if (color[i] == UNVISITED)
			sorting_dfs(g, i, color, &orderStack);
	}

	graph* gTranspon = graph_init(g->n);
	for (int i = 0; i < g->n; ++i) {
		color[i] = UNVISITED;
		list* vertecies = g->adj_list[i];
		while (vertecies) {
			add_arc(gTranspon, vertecies->ver, i);
			gTranspon;
			vertecies = vertecies->next;
		}
	}

	int sccCount = 0;
	int *result = (int*)malloc(g->n);
	for (int i = 0; i < g->n; i++) {
		list* components = NULL;
		int current = list_pop_up(&orderStack);
		if (color[current] == UNVISITED) {
			dfs(gTranspon, current, color, &components);
			while (components) {
				result[list_pop_up(&components)] = sccCount;
			}
			sccCount++;
		}
	}
	graph_free(gTranspon);
	return result;
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

//extra
void printComponents(int* components) {
	
}