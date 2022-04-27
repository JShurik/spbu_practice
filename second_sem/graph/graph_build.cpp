#include <iostream>
#include "graph.h" 

void graph_free(graph* g) {
	list* ptr = g->adj_list[0];
	list* t;
	while (ptr) {
		t = ptr->next;
		free(ptr);
		ptr = t;
	}
	free(g);
}

graph* graph_init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	g->n = n;
	g->adj_list = (list**)malloc(sizeof(list) * n);
	while (n > 0) {
		g->adj_list[g->n - n] = NULL;
		n--;
	}
	return g;
}

void add_arc(graph* g, int a, int b) {
	if (g == NULL) {
		printf("Empty graph\n");
		return;
	}
	if (a > g->n || a < 0 || b > g->n || b < 0) {
		printf("Incorrect input\n");
		return;
	}
	list* temp = (g)->adj_list[a];
	if (!temp)
		list_pushEmpty(&temp, b);
	else
		list_pushBack(&temp, b);
	(g)->adj_list[a] = temp;
}

void add_edge(graph* g, int a, int b) {
	add_arc(g, a, b);
	add_arc(g, b, a);
}

void del_arc(graph* g, int a, int b) {
	if (g == NULL) {
		printf("Empty graph\n");
		return;
	}
	if (a > g->n || a < 0 || b > g->n || b < 0) {
		printf("Incorrect input\n");
		return;
	}
	list* temp = g->adj_list[a];
	if (temp->ver == b) {
		temp = temp->next;
		if (temp) *(g->adj_list[a]) = *temp;
		else g->adj_list[a] = NULL;
		return;
	}
	while (temp->next->ver != b) {
		temp = temp->next;
		if (temp->next == NULL) break;
	}
	if (temp == NULL || temp->next == NULL) {
		printf("Error\n"); //vertex dosent exist
		return;
	}
	temp->next = temp->next->next;

}

void del_edge(graph* g, int a, int b) {
	del_arc(g, a, b);
	del_arc(g, b, a);
}

void graph_print(graph* g) {
	for (int i = 0; i < g->n; ++i) {
		printf("%i: ", i);
		list* vers = g->adj_list[i];
		while (vers) {
			printf("%i", vers->ver);
			if (vers->next) printf(", ");
			vers = vers->next;
		}
		printf("\n");
	}
}
