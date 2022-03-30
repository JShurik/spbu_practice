#include <iostream>
#include "graph.h"

typedef struct list {
	int ver;
	list* next;
} list;

typedef struct graph {
	int n;
	list* adj_list;
} graph;

void list_push(list** l, int n) {

}

graph* graph_init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	g->n = n;
	g->adj_list = (list*)malloc(sizeof(list)*n);
	while (n > 0) {
		list temp;
		g->adj_list[n - 1] = temp;
		n--;
	}
	return g;
}

void add_edge(graph** g, int a, int b) {
	if (*g == NULL) {
		//*g = (graph*)malloc(sizeof(graph));
	}
	
}

void del_edge(graph** g, int a, int b) {

}


void graph_print(graph* g);
void graph_free(graph* g);
