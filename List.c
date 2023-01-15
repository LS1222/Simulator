#ifndef __LIST_C__
#define __LIST_C__

#include "List.h"

ListNode* ListGet(List* list, int index) {
	ListNode* curr = NULL;

	// List too short.
	if (NULL == list)        return (NULL);
	if (list->size <= index) return (NULL);

	// Advance to index.
	curr = list->first;
	while (index-- > 0) curr = curr->next;

	return (curr);
}

ListNode* ListLast(List* list) {
	return (ListGet(list, list->size - 1));
}

// List Modification Methods.
int ListInsert(List* list, ListNode* node, int index) {
	ListNode* curr = NULL;

	if (NULL == list) return 0;
	if (NULL == node) return 0;
	if (index < 0)    return 0;

	// For indexes larger than size, append to the end.
	if (index > list->size) {
		list->last->next = node;
		node->prev = list->last;
		node->next = NULL;

	// Find the node at index.
	} else {
		curr = list->first;
		while (index-- > 0) curr = curr->next;
		node->next = curr->next;
		curr->next = node;
		node->prev = curr;
		node->next->prev = node;
	}

	return (++list->size);
}

ListNode* ListRemove(List* list, int index) {
	ListNode* removed = NULL;
	ListNode* curr    = NULL;

	if (NULL  == list)       return (NULL);
	if (index >= list->size) return (0);

	// Get the node pointing to the deletion spot.
	curr = list->first;
	while (index-- > 1) curr = curr->next;

	// Get the actual node to remove.
	if (list->size == 1) {
		removed = curr;
		list->first = NULL;
		list->last  = NULL;
	} else {
		removed = curr->next;
		curr->next = removed->next;
		curr->next->prev = curr;
	}

	list->size--;
	removed->next = NULL;
	removed->prev = NULL;

	return (removed);
}

void ListClear(List* list) {
	ListNode* curr = NULL;

	if (NULL != list) {
		while (list->size > 0) {
			curr = ListRemove(list, 0);
			free(curr);
		}
	}
}

int ListAppend(List* list, ListNode* node) {
	return (ListInsert(list, node, list->size));
}

// List Information Methods.
List* ListCopy(List* list) {
	ListNode* curr = NULL;
	ListNode* node = NULL;

	// Copy list core.
	List* copy = (List*)malloc(sizeof(List));
	copy->size = list->size;

	// Copy each node.
	curr = list->first;
	while (NULL != curr) {

		// Get the last node.
		node = copy->first;
		while (NULL != node->next) node = node->next;

		// Add the last node.
		copy->last = (ListNode*)malloc(sizeof(ListNode));
		node->next = copy->last;
		copy->last->prev = node;
		copy->last->next = NULL;
		copy->last->data = curr->data;

		// Get the next node.
		curr = curr->next;
	}

	return (copy);
}

int ListCount(List* list) {
	if (NULL == list) return (0);
	return (list->size);
}

void ListReverse(List* list) {
	if (NULL == list) return;
}

// List Data Methods.
void ListSort(List* list, int* comp(void*)) {
	if (NULL == list) return;
}

#endif // __LIST_C__