#include <iostream>
#include "graph.h"

typedef struct stack {
	list* data;
	stack* next;
} stack;

int change_color(int col) {
	if (col == 1)
		return 2;
	else
		return 1;
}

int* bipart_check_bfs(graph* g) { //1 - bipat, 0 - non bipart
	int* color = (int*)calloc(g->n, sizeof(int));
	int start_color = 1;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 0) {
			color[i] = start_color;
			list* queue = NULL;
			list_pushEmpty(&queue, i); //free
			while (queue) {
				int start_ver = list_pop_up(&queue);
				start_color = change_color(color[start_ver]);
				list* vers = g->adj_list[start_ver];
				while (vers) {
					int next_ver = vers->ver;
					if (color[next_ver] == 0) {
						color[next_ver] = start_color;
						list_pushBack(&queue, next_ver);
					}
					else {
						if (color[next_ver] == color[start_ver]) {
							free(color);
							return NULL;
						}
					}
					vers = vers->next;
				}
			}
			free_list(queue);
		}
	}
	return color;
}

int* bipart_check_dfs(graph* g) {
	int* color = (int*)calloc(g->n, sizeof(int));
	int start_color = 1;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 0) {
			color[i] = start_color;
			list* stack = NULL;
			list_pushEmpty(&stack, i);
			while (stack) {
				int start_ver = stack->ver;
				start_color = change_color(color[start_ver]);
				list* vers = g->adj_list[start_ver];
				if (vers) {
					int next_ver = vers->ver;
					while (color[next_ver]) {
						if (color[next_ver] == color[start_ver]) {
							free_list(stack);
							free(color);
							return NULL;
						}
						if (vers->next == NULL) break;
						vers = vers->next;
						next_ver = vers->ver;
					}
					if (color[next_ver] == 0) {
						list_push(&stack, next_ver);
						color[next_ver] = start_color;
					}
					else {
						list_pop_up(&stack);
					}
				}
				else {
					list_pop_up(&stack);
				}
			}
			free_list(stack);
		}
	}
	return color;
}

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
		if (!stack) list_pushEmpty(&stack, current);
		else list_push(&stack, current);
	}
	else if (color[current] == 1) {
		printf("Error: cycle has been found\n");
		return 0;
	}
	else if (color[current] == 2) {
		return 1;
	}
}

list** topological_sort(graph* g) {
	list** result = (list**)malloc(sizeof(list)*g->n);
	int* color = (int*)calloc(g->n, sizeof(int));
	list* stack = NULL;
	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 0) {
			if (g->adj_list[i]) {
				if (!vertex_check(g, &stack, color, i)) 
					return NULL;
			}
			color[i] = 2;
			if (!stack) list_pushEmpty(&stack, i);
			else list_push(&stack, i);
		}
	}

	free_list(stack);
	free(color);
	return result;
}

void print_parts(int* color) {
	int* color_copy = color;
	while (color_copy) {
		if (*color_copy == 1)
			printf("%i: first part\n", color_copy- color);
		else if (*color_copy == 2)
			printf("%i: second part\n", color_copy - color);
		else
			break;
		color_copy++;
	}
}