#include <iostream>
#include "DFA.h"

enum oper { UNION, INTERSEC, DIFF };


arc** clone_arcs_list(dfa* a) {
	arc** result = (arc**)malloc(sizeof(arc)*(a->numberOfStates+1));
	for (int i = 0; i <= a->numberOfStates; i++) {
		arc* temp = a->verticesList[i];
		result[i] = NULL;
		while (temp) {
			pushArc(&result[i], temp->node, temp->state);
			temp = temp->next;
		}
	}
	return result;
}

dfa* dfa_complement(dfa* a) {
	dfa* result = (dfa*)malloc(sizeof(dfa));
	int count = 0;
	if (result) {
		result->numberOfStates = a->numberOfStates;
		result->verticesList = clone_arcs_list(a);
		result->finalStates = (int*)malloc(a->numberOfStates - a->finalStatesNum);
		for (int i = 0; i <= result->numberOfStates; ++i) {
			int isFinalState = 0;
			for (int j = 0; j < a->finalStatesNum; ++j) {
				if (a->finalStates[j] == i) {
					isFinalState = 1;
					break;
				}
			}
			if (!isFinalState) {
				result->finalStates[count] = i;
				count++;
			}
		}
		result->finalStatesNum = count;
	}

	return result;
}

dfa* dfa_decart(dfa* a1, dfa* a2, oper operType) {
	dfa* result = dfaInit((a1->numberOfStates + 1) * (a2->numberOfStates + 1));
	for (int i = 0; i <= a1->numberOfStates; ++i) {
		for (int j = 0; j <= a2->finalStatesNum; ++j) {
			int from = (a2->finalStatesNum + 1) * i + j;
			arc* temp1 = a1->verticesList[i];
			arc* temp2 = a2->verticesList[j];
			int to = 0;
			if (temp1->state == temp2->state) {
				to = (a2->finalStatesNum + 1) * temp1->node + temp2->node;
				dfaSetArc(result, from, temp1->state, to);
				temp1 = temp1->next; temp2 = temp2->next;
				to = (a2->finalStatesNum + 1) * temp1->node + temp2->node;
				dfaSetArc(result, from, temp1->state, to);
			}
			else {
				to = (a2->finalStatesNum + 1) * temp1->node + temp2->next->node;
				dfaSetArc(result, from, temp1->state, to);
				to = (a2->finalStatesNum + 1) * temp1->next->node + temp2->node;
				dfaSetArc(result, from, temp2->state, to);
			}
			switch (operType)
			{
			case UNION:
				if (isFinal(a1, i) || isFinal(a2, j))
					addFinalState(result, from);
				break;
			case INTERSEC:
				if (isFinal(a1, i) && isFinal(a2, j))
					addFinalState(result, from);
				break;
			case DIFF:
				if (isFinal(a1, i) && !isFinal(a2, j))
					addFinalState(result, from);
				break;
			default:
				break;
			}

		}
	}
	return result;
}

dfa* dfa_intersection(dfa* a1, dfa* a2) {
	return dfa_decart(a1, a2, INTERSEC);
}

dfa* dfa_union(dfa* a1, dfa* a2) {
	return dfa_decart(a1, a2, UNION);
}

dfa* dfa_difference(dfa* a1, dfa* a2) {
	return dfa_decart(a1, a2, DIFF);
}