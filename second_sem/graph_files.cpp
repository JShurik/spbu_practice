#include <iostream>
#include <fstream>
#include "graph.h" 


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
			fgets(str, n * 3, f);
			while (*str != ':') str++;
			str++;
			while (*str) {
				if (*str > (char)9 || *str < (char)0) str++;
				add_arc(result, i, strtol(str, &str, 10));
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