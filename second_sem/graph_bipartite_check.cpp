#include <iostream>
#include "graph.h"

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
		}
	}
	//==
	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 1)
			printf("%i: first part\n", i);
		else
			printf("%i: second part\n", i);
	}
	//==
	return color;
}

int bipart_check_dfs(graph* g, int* color) {
	color = (int*)calloc(g->n, sizeof(int));
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
				int next_ver = vers->ver;
				while (color[next_ver]) {
					if (color[next_ver] == color[start_ver]) {
						return 0;
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
		}
	}
	return 1;
}