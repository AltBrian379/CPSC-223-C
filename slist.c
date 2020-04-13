#include "slist.h"
#include <stdbool.h>


snode* snode_create(int data, snode* next){
	snode* p = (snode*)malloc(sizeof(snode));
	p->data = data;
	p->next = next;
	return p;
}

slist* slist_create(void) {
	slist* list = (slist*)malloc(sizeof(slist));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

bool slist_empty(slist* list) {
	if (list->size == 0) { return true; }
	else { return false; }
}
size_t slist_size(slist* list) {
	return list->size;
}

void slist_popfront(slist* list) {
	if (list->size == 0) { return; }
	snode* p = list->head;
	list->head = list->head->next;
	free(p);
	--list->size;
	if (list->size == 0) { list->tail = NULL; }
}
void slist_popback(slist* list) {
	if (list->size == 0) { return; }
	snode* p = list->tail;
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		snode* q = list->head;
		while (q->next != p)
		{
			q = q->next;
		}
		list->tail = q;
		q->next = NULL;
	}
	free(p);
	--list->size;
	if (list->size == 0) { list->tail = NULL; }
}

void slist_pushfront(slist* list, int data) {
	snode* p = snode_create(data, NULL);
	p->next = list->head;
	list->head = p;
	if (list->size == 0) { list->tail = p; }
	++list->size;

}
void slist_pushback(slist* list, int data) {
	snode* p = snode_create(data, NULL);
	if (list->size == 0) { list->tail = p; }
	else {
	list->tail->next = p;
	list->tail = p;
	}
	if (list->size == 0) { list->head = p; }
	++list->size;
}

void slist_clear(slist* list){
	if (list->size == 0) { return; }
	snode* p = list->head;
	while (list->size != 0) { slist_popback(list); }
}

void slist_print(slist* list, const char* msg) {
	if (list->size == 0) { return; }
	snode* p = list->head;
	printf("%s\n", msg);
	while (p != NULL) {
		printf("%i --> %p\n",p->data, p->next);
		p = p->next;
	}
}

int slist_front(slist* list){

	return list->head->data;
}

int slist_back(slist* list) {
	return list->tail->data;
}

