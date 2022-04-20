#pragma once

typedef struct list {
	int ver;
	list* next;
} list;

typedef struct graph {
	int n;
	list** adj_list;
} graph;



list* getLast(list* last, int n);
void list_pushEmpty(list** l, int n);
void list_pushBack(list* l, int n);
void list_push(list* l, int n);
int list_pop_up(list** l);

void graph_free(graph* g);
graph* graph_init(int n);
void add_arc(graph* g, int a, int b);
void add_edge(graph* g, int a, int b);
void del_edge(graph* g, int a, int b);
void graph_print(graph* g);

int bipart_chek(graph* g, int* color);

graph* graph_read(const char* input);
void graph_write(graph* g, const char* output);