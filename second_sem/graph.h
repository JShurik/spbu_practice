#pragma once


typedef struct graph {
	int ver;
	//list*
} graph;

void graph_free(graph** gr);
graph* graph_init(int n);
void graph_print(graph* gr);
//add_arg, delete_arg (edge)
//BFS & DFS