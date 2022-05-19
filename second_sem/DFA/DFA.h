#pragma once
typedef struct arc {
	int state;
	int node;
	arc* next;
} arc;

typedef struct dfa {
	int n;
	int* finalState;
	int breakState;
	arc** conditions;
} dfa;

void pushArc(arc** l, int node, int state); //V

dfa* dfaInit(int n); //V
void dfaFree(dfa* a); //V
void dfaAddArc(int from, int cond, int to, dfa* a); //V
void dfaDeleteArc(int from, int to, dfa* a); //V
void dfaPrint(dfa* a, int x); //
int dfaCheck(dfa* a, int x); //
dfa* intGFA(int a); //
