#include <iostream>
#include "graph.h"

list* getLast(list* last) {
	if (last == NULL) {
		return NULL;
	}
	while (last->next) {
		last = last->next;
	}
	return last;
}

void list_pushEmpty(list** l, int n) {
	if (*l == NULL) {
		*l = (list*)malloc(sizeof(list));
		(*l)->ver = n;
		(*l)->next = NULL;
	}
	return;
}

void list_pushBack(list* l, int n) {
	list* last = getLast(l);
	list* temp = (list*)malloc(sizeof(list));
	temp->ver = n;
	temp->next = NULL;
	last->next = temp;
	return;
}

void graph_free(graph* g);

graph* graph_init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	g->n = n;
	g->adj_list = (list*)malloc(sizeof(list) * n);
	while (n > 0) {
		list* temp = NULL;
		list_pushEmpty(&temp, n);
		g->adj_list[n - 1] = *temp;
		n--;
	}
	return g;
}

void add_edge(graph** g, int a, int b) {
	if (*g == NULL) {
		*g = graph_init(2);
	}
	if (a <= (*g)->n || b <= (*g)->n) {
		list temp = (*g)->adj_list[a - 1];
		list_pushBack(&temp, b);
		(*g)->adj_list[a - 1] = temp;

		temp = (*g)->adj_list[b - 1];
		list_pushBack(&temp, a);
		(*g)->adj_list[b - 1] = temp;
	}

}

void del_edge(graph** g, int a, int b) {

}

void graph_print(graph* g) {
	list* temp = g->adj_list;
	for (int i = 0; i < g->n; ++i) {
		printf("%i: ", i + 1);
		list* vers = temp;
		while (vers->next != NULL) {
			vers = vers->next;
			printf("%i", vers->ver);
			if (vers->next != NULL) printf(", ");
		}
		temp++;
		printf("\n");
	}
}


