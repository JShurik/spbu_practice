#include <iostream>
#include "poly.h"

enum expt { E0, E1, E2 };

struct exception {
	int pos;
	expt e;
};

void poly_free(poly* p) {
	if (p == NULL)
		return;
	poly_free(p->next);
	free(p);
	return;
}

poly* poly_get_monomial(int coeff, int exp) {
	poly* result = (poly*)malloc(sizeof(poly));
	result->coeff = coeff; 
	result->exp = exp; 
	result->next = NULL;
	return result;
}

poly* poly_get(const char* input) {//, struct exception e = { 0, E0 }) {
	if (input == NULL) {
		std::cout << "Error: empty line\0";
		return NULL;
	}
	int state = 0; //4 conditions: 0 = sgn, 1 = digit, 2 = x, 3 = exp
	poly* result = poly_get_monomial(0, 0);
	char* pEnd;
	int num = 0, sgn = 1;
	
	for (int i = 0; i < strlen(input); ++i) {
		char symb = input[i];
		switch (state) {
		case 0: //sign
			if (symb >= '0' && symb <= '9') {
				state = 1;
				result->coeff = sgn*(int)strtol(input + i, &pEnd, 10);
				i = pEnd - input;
				if (input[i] == '\0')
					return result;
				else if (input[i] == '-' || input[i] == '+') {
					state = 0;
					poly* temp = poly_get_monomial(0,0);
					temp->next = result;
					result = temp;
					//poly_free(temp);
				}
				--i;
			}
			else if (symb == '+' || symb == '-') {
				state = 0;
				sgn = 1 - 2 * (sgn == '-');
			}
			else if(symb == 'x') {
				state = 2;
				result->coeff *= sgn;
			}
			else {
				std::cout << "Error: wrong input\0";
				return NULL;
			}
			break;

		case 1: //digit
			if (symb >= '0' && symb <= '9') { 
				state = 1;
			}			
			else if (symb == 'x') { 
				state = 2;
			}
			else if (symb == '+' || symb == '-') { 
				state = 0;
				sgn = 1 - 2 * (symb == '-');
			}
			else {
				std::cout << "Error: wrong input\0";
				return NULL;
			}
			break;

		case 2: //variable
			if (symb == '^') {
				state = 3;
			}
			else if (symb == '-' || symb == '+') {
				state = 0;
				result->exp = 1;
				poly* temp = poly_get_monomial(0, 0);
				temp->next = result;
				result = temp;
				//free temp
			}
			else if (symb == '\0') {
				result->exp = 1;
				return result;
			}
			else {
				std::cout << "Error: wrong input\n";
				return NULL;
			}
			break;

		case 3: //exp
			if (symb >= '0' && symb <= '9') {
				state = 1;
				result->exp = (int)strtol(input+i, &pEnd, 10);
				i = pEnd - input;
				if (input[i] == '\0')
					return result;
				--i;
				poly* temp = poly_get_monomial(0, 0);
				temp->next = result;
				result = temp;
				//free temp
			}
			else {
				std::cout << "Error: wrong input\n";
			}
			break;
		default:
			std::cout << "Error: unexpected symbols\n";
			break;
		}
	}	
}

void poly_print(poly* p) {
	while (p != NULL)
	{
		if (p->coeff != 1)
			printf("%i", p->coeff);
		if (p->coeff > 0)
			printf("+");
		if (p->exp != 0)
			printf("x");
		if (p->exp != 1)
			printf("^%i", p->exp);
		p = p->next;
	}
}


poly* poly_add(poly* p1, poly* p2);
poly* poly_multy(poly* p1, poly* p2);
