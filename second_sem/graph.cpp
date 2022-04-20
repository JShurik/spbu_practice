#include <iostream>
#include <fstream>
#include "graph.h"

list* getLast(list* last, int n) {
	if (last == NULL) {
		return NULL;
	}
	while (last->next) {
		if (last->ver == n) {
			return NULL;
		}
		last = last->next;
	}
	if (last->ver == n) return NULL;
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
	list* last = getLast(l, n);
	if (last) {
		list* temp = (list*)malloc(sizeof(list));
		temp->ver = n;
		temp->next = NULL;
		last->next = temp;
	}
	return;
}
void list_push(list* l, int n) {
	list* new_ = (list*)malloc(sizeof(list));
	new_->ver = n;
	if (l == NULL)
		l = new_;
	else
		new_->next = l; l = new_;
}
int list_pop_up(list** l) {
	if (*l != NULL) {
		list* new_ = *l;
		*l = new_->next;
		int res = new_->ver;
		new_ = NULL;
		free(new_);
		return res;
	}
	std::cout << "Steck is empty\n";
	return NULL;
}


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
		list_pushBack(temp, b);
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

//====== bipart check

int bipart_chek_dfs(const graph* g, int* color) {
	//int* first_part = (int*)malloc(sizeof(int));
	//int* second_part = (int*)malloc(sizeof(int));

	for (int i = 0; i < g->n; ++i) {
		if (color[i] == 0) {
			color[i] = 1;
			//list* vers = g->adj_list[i];

			list* stack = NULL;
			list_pushEmpty(&stack, i);
			

			while (stack) {
				int v = list_pop_up(&stack);

			}
		}
	}
}


//====== files
graph* graph_read(const char* path) {
	FILE* f = NULL;
	fopen_s(&f, path, "r");
	if (f) {
		int n = 0;
		char trash = '\n';
		if (fscanf_s(f, "%d", &n) == EOF) {
			printf("Error: unable to read the graph");
			return NULL;
		}
		fscanf_s(f, "%c", &trash);
		graph* result = graph_init(n);
		for (int i = 0; i < result->n; ++i) {
			char* str = (char*)malloc(n * 3);
			int j = 0;
			while (*(str + j - 1) != '\n') {
				if (fscanf_s(f, "%c", (str + j)) == EOF) {
					*(str + j) = '\n';
					break;
				}
				j++;
			}
			while (*str != ':') str++;
			str++;
			while (*str != '\n') {
				if (*str == ',') str++;
				int ver = strtol(str, &str, 10);
				if (result->adj_list[i])
					list_pushBack(result->adj_list[i], ver);
				else
					list_pushEmpty(&result->adj_list[i], ver);

			}

		}
		return result;
	}
	else {
		printf("Error: unable to open the file");
		return NULL;
	}
}
void graph_write(graph* g, const char* path) {
	FILE* f = NULL;
	fopen_s(&f, path, "w");
	if (f) {
		fprintf(f, "%i\n", g->n);
		for (int i = 0; i < g->n; ++i) {
			fprintf(f, "%i: ", i);
			list* vers = g->adj_list[i];
			while (vers) {
				fprintf(f, "%i", vers->ver);
				if (vers->next) fprintf(f, ", ");
				vers = vers->next;
			}
			fprintf(f, "\n");
		}
	}
}