#pragma once

typedef struct stack
{
	char data;
	stack *next;
} stack;
typedef struct stack_int {
	int data;
	stack_int* next;
} stack_int;

void push(stack** stk, char input);
void stack_free(stack* stk); 
char pop(stack** stk);

void push_i(stack_int** stk, int input);
void stack_free_i(stack_int* stk); 
int pop_i(stack_int** stk);

char* shuting_yard(char* input);
int calculation(char* input);