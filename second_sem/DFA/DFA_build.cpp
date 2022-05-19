#include <iostream>
#include "DFA.h"

void pushArc(arc** l, int node, int state) {
	arc* new_ = (arc*)malloc(sizeof(arc));
	new_->node = node;
	new_->state = state;
	if (*l == NULL)
		*l = new_;
	else
		new_->next = *l; *l = new_;
}

dfa* dfaInit(int n) {
	dfa* a = (dfa*)malloc(sizeof(dfa));
	a->n = n;
	//a->finalState = n - 1;
	a->breakState = n - 1;
	a->conditions = (arc**)malloc(sizeof(arc) * n);
	while (n > 0) {
		a->conditions[a->n - n] = NULL; //choose basic direction
		n--;
	}
	return a;
}

void dfaFree(dfa* a) {
	arc* ptr = a->conditions[0];
	arc* t;
	while (ptr) {
		t = ptr->next;
		free(ptr);
		ptr = t;
	}
	free(a);
}

void dfaAddArc(int from, int state, int to, dfa* a) {
	if (a) {
		arc* temp = a->conditions[from];
		pushArc(&temp, to, state);
		a->conditions[from] = temp;
	}
}

void dfaDeleteArc(int from, int to, dfa* a) {
	if (a) {
		//change direction
		arc* temp = a->conditions[from];
		if (temp->node == to) {
			temp = temp->next;
			if (temp) *(a->conditions[from]) = *temp;
			else 
				a->conditions[from] = NULL;
			return;
		}
		while (temp->next->node != to) {
			temp = temp->next;
			if (temp->next == NULL) break;
		}
		if (temp == NULL || temp->next == NULL) {
			return;
		}
		temp->next = temp->next->next;
	}
}

void dfaPrint(dfa* a, int x) {
	int current = 0;
	int num = 0;
	while (num != x) {

	}
}

int findPow(int a) {
	int result = 0;
	while (a > 0) {
		result++;
		a /= 2;
	}
	return result;
}

int dfaCheck(dfa* a, int x) {
	int current = 0;
	int pow = findPow(x);
	int num = 1;
	while (pow > 0) {
		arc* temp = a->conditions[current];
		while (temp->node != num) {
			temp = temp->next;
		}

	}
	if (current == a->finalState)
		return 1;
	else
		return 0;
}

dfa* intGFA(int a);