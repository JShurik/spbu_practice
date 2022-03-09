#include <iostream>
#include "poly.h"

#define ERROR(e_num) exept = { i, e_num }; \
					print_exeption(&exept); \
					return (poly*)NULL;

void poly_free(poly* p) {
	if (p == NULL)
		return;
	poly_free(p->next);
	free(p);
	return;
}

void print_exeption(exeption* ex) {

	printf("               ");
	for (int i = 0; i < ex->pos; ++i) {
		printf(" ");
	}
	printf("?\n");
	printf("Error. ");
	switch (ex->e)
	{
	case E0:
		printf("Unexpected symbols ");
		break;
	case E1:
		printf("Wrong order ");
		break;
	case E2:
		printf("Doubbled exponent ");
		break;
	case E3:
		printf("Doubbled signs ");
		break;
	case E4:
		printf("Doubbled variable ");
		break;
	default:
		printf("Unknown error ");
		break;
	}
	printf("on %i position\n", ex->pos);
}

poly* poly_get_monomial(int coeff, int exp) {
	poly* result = (poly*)malloc(sizeof(poly));
	result->coeff = coeff; 
	result->exp = exp; 
	result->next = NULL;
	return result;
}

void poly_merge(poly** p1, poly* p2) {
	int is_min = 1;
	while (p2 != NULL) 
	{
		poly* monomial = poly_get_monomial(p2->coeff, p2->exp);
		poly* main_list = *p1;
		poly* prev = NULL;
		while (main_list != NULL) {
			if (monomial->exp > main_list->exp) {
				monomial->next = main_list;
				main_list = monomial;
				is_min = 0;
				break;
			}
			else if (monomial->exp == main_list->exp) {
				main_list->coeff += monomial->coeff;
				is_min = 0;
				break;
			}
			else {
				poly* temp = poly_get_monomial(main_list->coeff, main_list->exp);
				temp->next = prev;
				prev = temp;
				is_min = 1;
			}
			main_list = main_list->next;
		}
		if (prev) {
			if (is_min)
				prev->next = monomial;
			else
				prev->next = main_list;
			*p1 = prev;
		}
		else {
			if (main_list) {
				*p1 = main_list;
			}
			else {
				*p1 = monomial;
			}
		}
		p2 = p2->next;
	}
}

poly* poly_get(const char* input) {//, struct exception e = { 0, E0 }) {
	if (input == NULL) {
		std::cout << "Error: empty line\0";
		return (poly*)NULL;
	}
	exeption exept;
	int sgn = 1, state = 0; //4 conditions: 0 = sgn, 1 = digit, 2 = x, 3 = exp
	poly* result = NULL;
	poly* temp_monomial = poly_get_monomial(0, 0);
	char* pEnd;	
	for (int i = 0; i < strlen(input); ++i) {
		char symb = input[i];
		switch (state) {
		case 0: //sign
			if (symb >= '0' && symb <= '9') {
				state = 1;
				temp_monomial->coeff = sgn*(int)strtol(input + i, &pEnd, 10);
				i = pEnd - input;
				if (input[i] == '\n') {
					poly_merge(&result, temp_monomial);
					return result;
				}
				else if (input[i] == '-' || input[i] == '+') {
					sgn = 1 - 2 * (input[i] == '-');
					poly_merge(&result, temp_monomial);
					temp_monomial = poly_get_monomial(0, 0);
				}
				--i;
			}
			else if (symb == '+' || symb == '-') {
				if (i == 0) {
					state = 0;
					sgn = 1 - 2 * (symb == '-');
				}
				else
					ERROR(E3)
			}
			else if (symb == 'x') {
				state = 2;
				temp_monomial->coeff = sgn * (temp_monomial->coeff + (temp_monomial->coeff == 0));
			}
			else if (symb == '^') {
				ERROR(E1)
			}
			else {
				ERROR(E0);
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
				ERROR(E0)
			}
			break;

		case 2: //variable
			if (symb == '^') {
				state = 3;
			}
			else if (symb == '-' || symb == '+') {
				state = 0;
				temp_monomial->exp = 1;
				sgn = 1 - 2 * (symb == '-');
				poly_merge(&result, temp_monomial);
				temp_monomial = poly_get_monomial(0, 0);
			}
			else if (symb == '\n') {
				temp_monomial->exp = 1;
				poly_merge(&result, temp_monomial);
				return result;
			}
			else if (symb == 'x') {
				ERROR(E4)
			}
			else if (symb >= '0' && symb <= '9') {
				ERROR(E1)
			}
			else {
				ERROR(E0)
			}
			break;

		case 3: //exp
			if (symb >= '0' && symb <= '9') {
				state = 1;
				temp_monomial->exp = (int)strtol(input+i, &pEnd, 10);
				i = pEnd - input;
				sgn = 1 - 2 * (input[i] == '-');
				if (input[i] == '\n') {
					poly_merge(&result, temp_monomial);
					return result;
				}		
				--i;
				poly_merge(&result, temp_monomial);
				temp_monomial = poly_get_monomial(0, 0);
			}
			else if (symb == '^') {
				ERROR(E2)
			}
			else if (symb == 'x' || symb == '+' || symb == '-'){
				ERROR(E1)
			}
			else{
				ERROR(E0)
			}
			break;
		default:
			ERROR(E0)
			break;
		}
	}	
}

void poly_print(poly* p) {

	while (p != NULL)
	{
		if (p->coeff > 0)
			printf("+");
		if (p->coeff != 0)
			printf("%i", p->coeff);
		if (p->exp != 0)
			printf("x");
		if (p->exp != 1 && p->exp != 0)
			printf("^%i", p->exp);
		p = p->next;
	}
	std::cout << std::endl;
}

poly* poly_add(poly* p1, poly* p2) {
	poly* result = p1;
	poly_merge(&result, p2);
	return result;
}

poly* poly_multy(poly* p1, poly* p2) {
	poly* result = (poly*)malloc(sizeof(poly*));
	result = poly_get_monomial(0, 0);
	poly* a = p1;
	while (p1 != NULL) {
		poly* b = p2;

	}
	return NULL;
}