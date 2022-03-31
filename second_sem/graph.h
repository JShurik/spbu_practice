#pragma once

typedef struct list {
	int ver;
	list* next;
} list;

typedef struct graph {
	int n;
	list* adj_list;
} graph;



list* getLast(list* last);
void list_pushEmpty(list** l, int n);
void list_pushBack(list* l, int n);

void graph_free(graph* g);
graph* graph_init(int n);
void add_edge(graph** g, int a, int b);
void del_edge(graph** g, int a, int b);
void graph_print(graph* g);


