#include <iostream>
#include "calculator.h"

void push(stack** stk, char input) {
	stack* new_ = (stack*)malloc(sizeof(stack));
	new_->data = input;
	if (stk == NULL)
		*stk = new_;
	else
		new_->next = *stk; *stk = new_;
}
void stack_free(stack* stk) {
	stack* t;
	while (stk) {
		t = stk->next;
		free(stk);
		stk = t;
	}
	return;
}
char pop(stack** stk) {
	if (*stk != NULL) {
		stack* new_ = *stk;
		*stk = new_->next;
		char res = new_->data;
		new_ = NULL;
		free(new_);
		return res;
	}
	std::cout << "Steck is empty\0";
	return NULL;
}

void push_i(stack_int** stk, int input) {
	stack_int* new_ = (stack_int*)malloc(sizeof(stack_int*));
	new_->data = input;
	if (stk == NULL)
		*stk = new_;
	else
		new_->next = *stk; *stk = new_;
}
void stack_free_i(stack_int* stk) {
	stack_int* t;
	while (stk) {
		t = stk->next;
		free(stk);
		stk = t;
	}
	return;
}
int pop_i(stack_int** stk) {
	if (*stk != NULL) {
		stack_int* new_ = *stk;
		*stk = new_->next;
		int res = new_->data;
		new_ = NULL;
		free(new_);
		return res;
	}
	std::cout << "Steck is empty\0";
	return NULL;
}

int compare_opers(char oper1, char oper2) {
	if (oper1 == '(' || oper2 == '(')
		return 1;
	if (oper1 == '*' || oper1 == '/') {
		if (oper2 == '*' || oper2 == '/')
			return 0;
		else if (oper2 == '+' || oper2 == '-')
			return 1;
	}
	else if (oper1 == '-' || oper1 == '+') {
		if (oper2 == '*' || oper2 == '/')
			return -1;
		else if (oper2 == '+' || oper2 == '-')
			return 0;
	}

}

char* shuting_yard(char* input) {
	char* output = (char*)malloc(sizeof(char)*strlen(input) + 4);
	stack* opers = (stack*)malloc(sizeof(stack));
	opers = NULL;
	int count = 0;
	char* s = (char*)input;
	while (*s != '\n') {
		if (*s >= '0' && *s <= '9') {
			output[count] = *s;
			count++;
		}
		else if (*s == '+' || *s == '-' || *s == '/' || *s == '*') {
			output[count] = ' ';
			count++;
			if (opers) {
				if (compare_opers(*s, opers->data) - 1) {
					while (compare_opers(*s, opers->data) - 1 && opers->data != '(') {
						output[count] = pop(&opers);
						count++;
						output[count] = ' ';
						count++;
						if (opers == NULL) break;
					}
				}
			}
			push(&opers, *s);
		}
		else if (*s == '(') {
			push(&opers, *s);
		}
		else if ((*s == 'G' && *(s + 1) == 'C' && *(s + 2) == 'D') || (*s == 'L' && *(s + 1) == 'C' && *(s + 2) == 'M')) {
			push(&opers, *s);
			s += 2;
		}
		else if (*s == ',') {
			output[count] = ' ';
			count++;
			while (opers->data != '(') { ///!!!!
				char t = pop(&opers);
				output[count] = ' ';
				count++;
				output[count] = t;
				count++;
				if (t == 'G') {
					output[count++] = 'C';
					output[count++] = 'D';
				}
				if (t == 'L') {
					output[count++] = 'C';
					output[count++] = 'M';
				}
				if (opers == NULL) break;
			}
		}
		else if (*s == ')') {
			if (opers) {
				if (opers->data == '(') {
					pop(&opers);
				}
				while (opers->data != '(') { ///!!!!
					char t = pop(&opers);
					output[count] = ' ';
					count++;
					output[count] = t;
					count++;
					if (t == 'G') {
						output[count++] = 'C';
						output[count++] = 'D';
					}
					if (t == 'L') {
						output[count++] = 'C';
						output[count++] = 'M';
					}
					if (opers == NULL) break;
				}
				if (opers)
					if (opers->data == '(') pop(&opers);
			}

		}
		else if (*s == ' ') {}
		else {
			printf("Error: Unknown symbols");
			return NULL;
		}
		s++;
	}
	if (opers) {
		while (opers) {
			char t = pop(&opers);
			if (t != '(') {
				output[count] = ' ';
				count++;
				output[count] = t;
				if (t == 'G') {
					output[count++] = 'C';
					output[count++] = 'D';
				}
				if (t == 'L') {
					output[count++] = 'C';
					output[count++] = 'M';
				}
			}
			count++;
		}
	}
	output[count] = '\0';
	return output;
}

int gcd(int a, int b) {
	if ((a == 0) || (b == 0)) return (a + b);
	return gcd(b % a, a);
}

int calculation(char* input) {
	char* s = input;
	int result = 0;
	stack_int* nums = NULL;
	while (*s != '\0') {
		if (*s >= '0' && *s <= '9') {
			push_i(&nums, (int)strtol(s, &s, 10));
			s++;
		}
		else if (*s == ' ') {
			s++;
		}
		else {
			int a = pop_i(&nums);
			int b = pop_i(&nums);
			switch (*s)
			{
			case '+':
				result = b + a; s++;
				break;
			case '-':
				result = b - a; s++;
				break;
			case '*':
				result = b * a; s++;
				break;
			case '/':
				result = b / a; s++;
				break;
			case 'L':
				result = (b*a) / gcd(a, b); s += 3;
				break;
			case 'G':
				result = gcd(a, b); s += 3;
				break;
			}
			push_i(&nums, result);
		}
	}
	return result;
}