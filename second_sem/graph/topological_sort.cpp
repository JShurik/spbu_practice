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
		if (!(*stack)) list_pushEmpty(stack, current);
		else list_push(stack, current);
	}
	else if (color[current] == 1) {
		printf("Error: cycle has been found\n");
		return 0;
	}
	else if (color[current] == 2) {
		return 1;
	}
}

int num_deep(list* stack, int num) {
	int deep = 0;
	while (stack->ver != num) {
		deep++;
		stack = stack->next;
	}
	return deep;
}

void list_assign(list** target, list* sourse) {
	if (sourse) {
		list_pushEmpty(target, sourse->ver);
		sourse = sourse->next;
		while (sourse) {
			list_pushBack(target, sourse->ver);
			sourse = sourse->next;
		}
	}
}

list** topological_sort(graph* g) {
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
				list_pushEmpty(&stack, i);
			}
		}
	}
	list* stack_copy = stack;
	list** result = (list**)malloc(sizeof(list) * g->n);
	for (int i = 0; i < g->n; ++i)
		result[i] = NULL;
	for (int i = 0; i < g->n; ++i) {
		int curr = stack_copy->ver;
		list_assign(&result[i], g->adj_list[curr]);
		list* tmp = result[i];
		while (tmp) {
			tmp->ver = num_deep(stack, tmp->ver);
			tmp = tmp->next;
		}
		stack_copy = stack_copy->next;
	}
	free_list(stack);
	free(color);
	return result;
}