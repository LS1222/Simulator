#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct {
	void*     data;
	ListNode* next;
	ListNode* prev;
} ListNode;

typedef struct {
	ListNode* first;
	int       size;
} List;


// Access Methods.
ListNode* ListGet    (List* list, int index);
ListNode* ListLast   (List* list);

// List Modification Methods.
void      ListInsert (List* list, ListNode* node, int index);
ListNode* ListRemove (List* list, int index);
void      ListClear  (List* list);
void      ListAppend (List* list, ListNode* node);

// List Information Methods.
List*     ListCopy   (List* list);
int       ListCount  (List* list);
void      ListReverse(List* list);

// List Data Methods.
void      ListSort   (List* list, int* comp(void*));

#endif // __LIST_H__