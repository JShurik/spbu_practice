#pragma once

typedef struct arc {
	int node;
	int state;
	arc* next;
} arc;

typedef struct dfa {
	int numberOfStates;
	int finalStatesNum;
	int* finalStates;
	arc** verticesList;
} dfa;

void pushArc(arc** l, int node, int state);
dfa* dfaInit(int n);
void dfaFree(dfa* a);
void addFinalState(dfa* a, int finIndex);
void dfaSetArc(dfa* a, int from, int state, int to);
void dfaResetArcs(int from, int to, dfa* a);
int isFinal(dfa* a, int ver);
int dfaCheck(dfa* a, int x);
void dfaPrint(dfa* a, int x);
dfa* intDFA(int a);

arc** clone_arcs_list(dfa* a);
dfa* dfa_complement(dfa* a);
dfa* dfa_intersection(dfa* a1, dfa* a2);
dfa* dfa_union(dfa* a1, dfa* a2);
dfa* dfa_difference(dfa* a1, dfa* a2);