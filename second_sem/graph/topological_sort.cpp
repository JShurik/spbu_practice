#include <iostream>
#include "graph.h"

int vertex_check(graph* g, list** stack, int* color, int current) {
	if (color[current] == 0) {
		color[current] = 1;
		list* vertexes = g->adj_list[current];
		if (vertexes) {
			while (vertexes) {
				if (!vertex_check(g, stack, color, vertexes->ver))
					return 0;
				vertexes = vertexes->next;
			}
		}
		color[current] = 2;
		list_push(stack, current);
	}
	else if (color[current] == 1) {
		return 0;
	}
	else if (color[current] == 2) {
		return 1;
	}
}

int* topological_sort(graph* g) {
	int* color = (int*)calloc(g->n, sizeof(int));
	list* stack = NULL;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 0) {
			if (g->adj_list[i]) {
				if (!vertex_check(g, &stack, color, i))
					return NULL;
			}
			if (!stack) {
				color[i] = 2;
				list_push(&stack, i);
			}
		}
	}
	int* result = (int*)malloc(g->n);
	for (int i = 0; i < g->n; ++i) {
		result[i] = list_pop_up(&stack);
	}
	return result;
}

int deep(int* arr, int n) {
	int* arr_copy = arr;
	while (arr) {
		if (n == *arr)
			return arr - arr_copy;
		arr++;
	}
}

list** change_vertexes(int* order, graph* g) {
	list** result = (list**)malloc((g)->n);
	for (int i = 0; i < (g)->n; ++i)
		result[i] = NULL;
	for (int i = 0; i < (g)->n; ++i) {
		list_assign(&result[i], (g)->adj_list[order[i]]);
		list* tmp = result[i];
		while (tmp) {
			tmp->ver = deep(order, tmp->ver);
			tmp = tmp->next;
		}
	}
	return result;
}