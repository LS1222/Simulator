#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

struct _list_node {
	void*            data;
	struct _list_node* next;
	struct _list_node* prev;
};

typedef struct _list_node ListNode;

typedef struct {
	ListNode* first;
	ListNode* last;
	int              size;
} List;


// Access Methods.
ListNode* ListGet    (List* list, int index);
ListNode* ListLast   (List* list);

// List Modification Methods.
int       ListInsert (List* list, ListNode* node, int index);
ListNode* ListRemove (List* list, int index);
void      ListClear  (List* list);
int       ListAppend (List* list, ListNode* node);

// List Information Methods.
List*     ListCopy   (List* list);
int       ListCount  (List* list);
void      ListReverse(List* list);

// List Data Methods.
void      ListSort   (List* list, int* comp(void*));

#endif // __LIST_H__