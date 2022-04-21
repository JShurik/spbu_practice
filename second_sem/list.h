#pragma once

typedef struct list {
	int ver;
	list* next;
} list;


list* getLast(list* last, int n);
void list_pushEmpty(list** l, int n);
void list_pushBack(list** l, int n);
void list_push(list** l, int n);
int list_pop_up(list** l);