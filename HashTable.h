#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "List.h"

#define HASH_ARRAY_SIZE 25

typedef struct {
	int hash_low;
	int hash_high;
} HashValue;

typedef struct {
	List*     list_of_values;
	HashValue key;
} HashItem;

typedef struct {
	int num_of_items;
	HashItem hash_array[HASH_ARRAY_SIZE];
} HashTable;

// Functions.
HashValue FromString(char* hash);


#endif // __HASH_TABLE_H__
