#include <iostream>
#include "trees.h"
#include "graph.h"
#include "calculator.h"

using namespace std;

int main()
{
	graph* g = graph_read("input.txt");
	graph_print(g);
	graph_write(g, "output.txt");

	if (bipart_check_bfs(g)) {
		printf("graph is bipartial\n");
		print_parts(bipart_check_dfs(g));
	}
	else {
		printf("graph is not bipartial\n");
	}

	int* order = topological_sort(g);
	if (order) {
		g->adj_list = change_vertexes(order, g);
		graph_print(g);
	}
	else
		printf("Error: cycle has been found\n");

	tarjan_scc(g);
	scc(g);
}