#include <iostream>
#include "list.h"

void free_list(list* l) {
	list* t;
	while (l) {
		t = l->next;
		free(l);
		l = t;
	}
	return;
}

list* getLast(list* last, int n) {
	if (last == NULL) {
		return NULL;
	}
	while (last->next) {
		if (last->ver == n) {
			return NULL;
		}
		last = last->next;
	}
	if (last->ver == n) return NULL;
	return last;
}

void list_pushEmpty(list** l, int n) {
	if (*l == NULL) {
		*l = (list*)malloc(sizeof(list));
		(*l)->ver = n;
		(*l)->next = NULL;
	}
	return;
}

void listPushBack(list** l, int n) {
	list* last = getLast(*l, n);
	if (last) {
		list* temp = (list*)malloc(sizeof(list));
		temp->ver = n;
		temp->next = NULL;
		last->next = temp;
	}
	else
		list_pushEmpty(l, n);
	return;
}

void listPushUp(list** l, int n) {
	if (*l) {
		list* new_ = (list*)malloc(sizeof(list));
		new_->ver = n;
		if (*l == NULL)
			*l = new_;
		else
			new_->next = *l; *l = new_;
	}
	else
		list_pushEmpty(l, n);

}

int list_pop_up(list** l) {
	if (*l != NULL) {
		list* new_ = *l;
		*l = new_->next;
		int res = new_->ver;
		new_ = NULL;
		free(new_);
		return res;
	}
	std::cout << "Steck is empty\n";
	return NULL;
}

void list_assign(list** target, list* sourse) {
	if (sourse) {
		list_pushEmpty(target, sourse->ver);
		sourse = sourse->next;
		while (sourse) {
			listPushBack(target, sourse->ver);
			sourse = sourse->next;
		}
	}
}