#include "dlist.h"
#include <stdbool.h>

dnode* dnode_create(int data, dnode* prev, dnode* next) {
	dnode* p = (dnode*)malloc(sizeof(dnode));
	p->data = data;
	p->prev = prev;
	p->next = next;

	return p;
}
dlist* dlist_create(void) {
	dlist* p = (dnode*)malloc(sizeof(dlist));
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;

	return p;

}

bool dlist_empty(dlist* list) {
	if (list->size == 0) { return true; }
	else { return false; }
}

size_t dlist_size(dlist* list) {
	return list->size;
}

void dlist_popfront(dlist* list) {
	if (list->size == 0) { return; }
	dnode* p = list->head;
	list->head = list->head->next;
	free(p);
	--list->size;
	if (list->size == 0) { list->tail = NULL; }
}
void dlist_popback(dlist* list) {
	if (list->size == 0) { return; }
	dnode* p = list->tail;
	list->tail = list->tail->prev;
	free(p);
	--list->size;
	if (list->size == 0) { list->head = NULL; }
}

void dlist_pushfront(dlist* list, int data) {
	dnode* p = dnode_create(data, NULL, NULL);
	if (list->size == 0) { list->head = p; list->tail = p; }
	else {
		p->next = list->head;
		list->head->prev = p;
		list->head = p;
	}
	++list->size;
}
void dlist_pushback(dlist* list, int data) {
	dnode* p = dnode_create(data, NULL, NULL);
	if (list->size == 0) { list->tail = p; list->head = p; }
	else {
		p->prev = list->tail;
		list->tail->next = p;
		list->tail = p;
	}
	++list->size;
}

void dlist_clear(dlist* list) {
	while (list->size != 0) {
		dlist_popfront(list);
	}
}
void dlist_print(dlist* list, const char* msg) {
	dnode* p = list->head;
	printf("%s\n", msg);
	while (p != NULL)
	{
		printf("%p <-- %i (%p) --> %p\n",p->prev,p->data, p,p->next);
		p = p->next;
	}

}

int dlist_front(dlist* list) {
	return list->head->data;
}
int dlist_back(dlist* list) {
	return list->tail->data;
}

