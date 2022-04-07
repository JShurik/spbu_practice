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

void list_free(list** l) {
	list *t;
	while (l) {
		t = (*l)->next;
		free(*l);
		*l = t;
	}
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

void graph_free(graph* g) {

}

graph* graph_init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	g->n = n;
	g->adj_list = (list*)malloc(sizeof(list) * n);
	while (n > 0) {
		list* temp = NULL;
		list_pushEmpty(&temp, -1);
		g->adj_list[g->n - n] = *temp;
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
	list temp = (g)->adj_list[a];
	if (temp.ver == -1) {
		temp.ver = b;
	}
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
	list* temp = g->adj_list + a;
	if (temp->ver == b) {
		temp = temp->next;
		*(g->adj_list + a) = *temp;
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
	list* temp = g->adj_list;
	for (int i = 0; i < g->n; ++i) {
		printf("%i: ", i);
		list* vers = temp;
		while (vers) {
			if (vers->ver != -1)
				printf("%i", vers->ver);
			else
				printf("No connection");
			if (vers->next) printf(", ");
			vers = vers->next;
		}
		temp++;
		printf("\n");
	}
}