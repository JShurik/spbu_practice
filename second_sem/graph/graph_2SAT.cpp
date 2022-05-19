#include <iostream>
#include "graph.h"

int countVariables(char* expression) {
	int numberOfVars = 0;
	while (*expression != '\n') {
		if (*expression == 'x') {
			expression++;
			int xNum = (int)strtol(expression, nullptr, 10);
			if (xNum > numberOfVars)
				numberOfVars = xNum;
		}
		expression++;
	}
	return numberOfVars;
}

graph* readExpression(char* expression) {
	int vertexesNum = countVariables(expression) * 2;
	graph* result = graph_init(vertexesNum);
	int openBrackets = 0, closedBrackets = 0;
	int not_ = 1, xFst = 0, xSec = 0;
	while (*expression != '\n') {
		switch (*expression) {
		case 'x':
			expression++;
			xSec = strtol(expression, &expression, 10)*not_;
			if (xSec == 0) {
				printf("ERROR: wrong indexes\n");
				return NULL;
			}
			if (xFst == 0)
				xFst = xSec;
			else {
				xFst *= -1;
				int from1 = (vertexesNum + xFst) * (xFst < 0) + (xFst - 1) * (xFst > 0);
				int to1 = (vertexesNum + xSec) * (xSec < 0) + (xSec - 1) * (xSec > 0);
				xFst *= -1;
				xSec *= -1;
				int from2 = (vertexesNum + xSec) * (xSec < 0) + (xSec - 1) * (xSec > 0);
				int to2 = (vertexesNum + xFst) * (xFst < 0) + (xFst - 1) * (xFst > 0);
				add_arc(result, from1, to1);
				add_arc(result, from2, to2);
				xFst = 0;
				xSec = 0;
			}
			break;
		case '~':
			not_ = -1;
			expression++;
			break;
		case '(':
			expression++;
			openBrackets++;
			break;
		case ')':
			expression++;
			closedBrackets++;
			break;
		case 'V':
		case '&':
			not_ = 1;
		case ' ':
			expression++;
			break;
		default:
			printf("ERROR: unkwown symbols\n");
			return NULL;
		}
	}
	if (closedBrackets != openBrackets) {
		printf("ERROR: wrong input\n");
		return NULL;
	}
	return result;
}

int* solveExpression(graph* expression) {
	int* comps = tarjan_scc(expression);
	for (int i = 0; i < (expression->n/2); ++i) {
		int indX = i, indNotX = expression->n - indX - 1;
		if (comps[indX] == comps[indNotX]) {
			printf("No solution\n");
			return NULL;
		}
	}
	int* result = (int*)malloc(expression->n / 2);
	for (int i = 0; i < (expression->n / 2); ++i) {
		int indX = i, indNotX = expression->n - indX - 1;
		if (comps[indX] < comps[indNotX])
			result[i] = 1;
		else
			result[i] = 0;
	}
	return result;
}

void printSolution(int* result, int numberOfVars) {
	if (result) {
		for (int i = 0; i < numberOfVars; ++i) {
			if (result[i] == 0)
				printf("x%d: false\n", i+1);
			else
				printf("x%d: true\n", i+1);
		}
	}
}