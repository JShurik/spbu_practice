#pragma once

typedef struct list {
	int ver;
	list* next;
} list;

void free_list(list* l);

list* getLast(list* last, int n);
void list_pushEmpty(list** l, int n);
void listPushBack(list** l, int n);
void listPushUp(list** l, int n);
int list_pop_up(list** l);
void list_assign(list** target, list* sourse);