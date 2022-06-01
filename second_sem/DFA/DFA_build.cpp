#include <iostream>
#include "DFA.h"

void pushArc(arc** l, int node, int state) {
	arc* new_ = (arc*)malloc(sizeof(arc));
	new_->node = node;
	new_->state = state;
	new_->next = NULL;
	if (*l == NULL)
		*l = new_;
	else
		new_->next = *l; *l = new_;
}

dfa* dfaInit(int n) {
	dfa* result = (dfa*)malloc(sizeof(dfa));
	if (result) {
		result->numberOfStates = n;
		result->finalStatesNum = 0;
		result->finalStates = NULL;
		result->verticesList = (arc**)malloc(sizeof(arc) * (n+1));
		while (n >= 0) {
			result->verticesList[n] = NULL;
			pushArc(&result->verticesList[n], result->numberOfStates, 0);
			pushArc(&result->verticesList[n], result->numberOfStates, 1);
			n--;
		}
	}
	else
		return NULL;
	return result;
}

void dfaFree(dfa* a) {
	arc* ptr = a->verticesList[0];
	arc* t;
	while (ptr) {
		t = ptr->next;
		free(ptr);
		ptr = t;
	}
	free(a);
}

void addFinalState(dfa* a, int finIndex) {
	a->finalStatesNum += 1;
	int* temp = (int*)malloc(a->finalStatesNum * sizeof(int));
	memcpy((void*)temp, (void*)a->finalStates, (a->finalStatesNum-1) * sizeof(int));
	free(a->finalStates);
	temp[a->finalStatesNum - 1] = finIndex;
	a->finalStates = temp;
}

void dfaSetArc(dfa* a, int from, int state, int to) {
	arc* temp = a->verticesList[from];
	while (temp->state != state) {
		temp = temp->next;
	}
	temp->node = to;
}

void dfaResetArcs(int from, int to, dfa* a) {
	for (int i = 0; i < a->numberOfStates; ++i) {
		dfaSetArc(a, i, 0, a->numberOfStates);
		dfaSetArc(a, i, 1, a->numberOfStates);
	}
}

int isFinal(dfa* a, int ver) {
	for (int i = 0; i <= a->finalStatesNum; ++i) {
		if (ver == a->finalStates[i])
			return 1;
	}
	return 0;
}

int dfaCheck(dfa* a, int x) {
	int currentNode = 0, currentState = 0, num = x;
	while (num > 0) {
		arc* temp = a->verticesList[currentNode];
		if (temp == NULL) {
			return 0;
		}
		currentState = num & 1;
		while (temp->state != currentState) {
			temp = temp->next;
		}
		currentNode = temp->node;
		num >>= 1;
	}
	return isFinal(a, currentNode);
}

void dfaPrint(dfa* a, int x) {
	for (int i = 0; i < x; i++) {
		if (dfaCheck(a, i)) {
			printf("%d ", i);
		}
	}
	printf("\n");
}

dfa* intDFA(int a) {
	int count = 0;
	while (a >= (1 << count)) 
		count++;
	dfa* result = dfaInit(count+1);
	addFinalState(result, count);
	for (int i = 0; i <= count; ++i) {
		int currenState = a & 1;
		dfaSetArc(result, i, currenState, i+1);
		a >>= 1;
	}
	return result;
}