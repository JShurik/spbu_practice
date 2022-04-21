#include <iostream>
#include "trees.h"
#include "graph.h"
#include "calculator.h"

using namespace std;

int main()
{
	

	graph* gr = graph_init(5);
	add_edge(gr, 1, 2);
	add_edge(gr, 3, 2);
	add_edge(gr, 4, 2);
	add_edge(gr, 4, 2);
	add_edge(gr, 0, 1);
	graph_print(gr);
	del_edge(gr, 1, 0);
	del_edge(gr, 2, 3);
	printf("\n");
	graph_print(gr);
	graph_free(gr);
	printf("\n");


	graph* grr = graph_read("input.txt");
	//graph_write(grr, "output.txt");


	graph_print(grr);
	printf("\n");
	int* color = (int*)malloc(sizeof(int));
	if (bipart_check_bfs(grr, color)) {
		printf("Graph is bipartial\n");
	}
	else
		printf("Graph is not bipartial\n");
	

	if (bipart_check_dfs(grr, color))
		printf("Graph is bipartial\n");
	else
		printf("Graph is not bipartial\n");


	//char* str = (char*)malloc(sizeof(char*));
	//char* str2 = (char*)malloc(sizeof(char*));
	//Ex 1-4
	/*printf("Enter expression: ");
	fgets(str, 512, stdin);
	char* pol_form = shuting_yard(str);
	if (pol_form) {
		int res = calculation(pol_form);
		cout << pol_form << endl;
		cout << res << endl;
	}

	printf("Enter elements: ");
	fgets(str, 256, stdin);
	tree_print(tree_sort(str));
	int* arr = (int*)malloc(sizeof(int)*strlen(str));
	int i = 0;
	tree_to_array(tree_sort(str), arr, &i);

	printf("Enter number: ");
	double num;
	scanf_s("%lf", &num);
	sb_number(num, get_stern_brocot_tree(24));*/

}