#include <iostream>
#include "poly.h"

#define ERROR(except, i, e_num) exept-> = { i, e_num }; \
					print_exeption(&exept); \
					poly_free(result); poly_free(temp_monomial); \
					return (poly*)NULL

#define RETURN_NULL(result, temp) poly_free(result); poly_free(temp); \
								return (poly*)NULL

enum state { SGN, DIGIT, X, EXP };

void poly_free(poly* p) {
	poly* t;
	while (p) {
		t = p->next;
		free(p);
		p = t;
	}
	return;
}

void print_exeption(exeption* ex) {
	printf("               ");
	for (int i = 0; i < ex->pos; ++i) {
		printf("~");
	}
	printf("^\n");
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
	if (result) {
		result->coeff = coeff;
		result->exp = exp;
		result->next = NULL;
	}
	return result;
}

void poly_clone(poly** target, poly* p) {
	poly_free(*target);
	*target = poly_get_monomial(0, 0);
	poly* temp = NULL;
	while (p) {
		if ((*target)->coeff == 0 && (*target)->exp == 0) {
			temp = *target;
		}
		else {
			temp = poly_get_monomial(0,0);
		}
		memcpy(temp, p, sizeof(poly));
		temp->next = NULL;
		(*target)->next = temp;
		*target = temp;
		p = p->next;
	}
	(*target)->next = NULL;
}

void poly_merge(poly** p1, poly* p2) {
	int is_min = 1;
	while (p2 != NULL) {
		poly* list = *p1;
		poly* prev = NULL;
		poly* p2_mono = poly_get_monomial(p2->coeff, p2->exp);
		while (list) {
			if (p2_mono->exp > list->exp) {
				p2_mono->next = list;
				poly_clone(&list, p2_mono);
				is_min = 0;
				break;
			}
			else if (p2_mono->exp == list->exp) {
				list->coeff += p2_mono->coeff;
				is_min = 0;
				break;
			}
			else {
				poly* temp = poly_get_monomial(list->coeff, list->exp);
				temp->next = prev;
				poly_clone(&prev, temp);
				poly_free(temp);
				is_min = 1;
			}
			list = list->next;
		}
		if (prev) {
			if (is_min)
				prev->next = p2_mono;
			else
				prev->next = list;
			**p1 = *prev;
		}
		else {
			if (list) {
				*p1 = list;
			}
			else {
				//*p1->coeff = p2_mono->coeff;
				*p1 = p2_mono;
				break;
			}
		}
		p2 = p2->next;
		//poly_free(list);
		//poly_free(prev);
		//poly_free(p2_mono);
	}
}

poly* poly_get(const char* input, exception* exep) {
	if (input == NULL) {
		std::cout << "Error: empty line\0"; 
		return (poly*)NULL;
	}
	//exeption exept;
	int sgn = 1;
	state s = SGN; 
	poly* result = NULL;
	poly* temp_monomial = poly_get_monomial(0, 0);
	char* pEnd = NULL;	
	for (int i = 0; i < strlen(input); ++i) {
		char symb = input[i];
		switch (s) {
		case SGN:
			if (symb >= '0' && symb <= '9') {
				s = DIGIT;
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
					s = SGN;
					sgn = 1 - 2 * (symb == '-');
				}
				else {
					*exep = { i, E3 };
					RETURN_NULL(result, temp_monomial);
				}
			}
			else if (symb == 'x') {
				s = X;
				temp_monomial->coeff = sgn * (temp_monomial->coeff + (temp_monomial->coeff == 0));
			}
			else if (symb == '^') {
				*exep = { i, E1 };
				RETURN_NULL(result, temp_monomial);
			}
			else {
				*exep = { i, E0 };
				RETURN_NULL(result, temp_monomial);
			}
			break;

		case DIGIT:
			if (symb >= '0' && symb <= '9') { 
				s = DIGIT;
			}			
			else if (symb == 'x') { 
				s = X;
			}
			else if (symb == '+' || symb == '-') { 
				s = SGN;
				sgn = 1 - 2 * (symb == '-');
			}
			else {
				*exep = { i, E0 };
				RETURN_NULL(result, temp_monomial);
			}
			break;

		case X:
			if (symb == '^') {
				s = EXP;
			}
			else if (symb == '-' || symb == '+') {
				s = SGN;
				temp_monomial->exp = 1;
				sgn = 1 - 2 * (symb == '-');
				poly_merge(&result, temp_monomial);
				temp_monomial = poly_get_monomial(0, 0);
			}
			else if (symb == '\n') {
				temp_monomial->exp = 1;
				poly_merge(&result, temp_monomial);
			}
			else if (symb == 'x') {
				*exep = { i, E4 };
				RETURN_NULL(result, temp_monomial);
			}
			else if (symb >= '0' && symb <= '9') {
				*exep = { i, E1 };
				RETURN_NULL(result, temp_monomial);
			}
			else {
				*exep = { i, E0 };
				RETURN_NULL(result, temp_monomial);
			}
			break;

		case EXP:
			if (symb >= '0' && symb <= '9') {
				s = DIGIT;
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
				*exep = { i, E2 };
				RETURN_NULL(result, temp_monomial);
			}
			else if (symb == 'x' || symb == '+' || symb == '-'){
				*exep = { i, E1 };
				RETURN_NULL(result, temp_monomial);
			}
			else{
				*exep = { i, E0 };
				RETURN_NULL(result, temp_monomial);
			}
			break;
		default:
			*exep = { i, E0 };
			RETURN_NULL(result, temp_monomial);
			break;
		}
	}
	return result;
}

void poly_print(poly* p) {
	while (p != NULL)
	{
		if (p->coeff > 0)
			printf("+");
		if (p->coeff != 0 && !(p->coeff == 1 && p->exp != 0))
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

	while (p1) {
		while (p2) {
			poly_merge(&result, poly_get_monomial(p1->coeff*p2->coeff, p1->exp + p2->exp));
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return NULL;
}
