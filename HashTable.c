#ifndef __HASH_TABLE_C__
#define __HASH_TABLE_C__

#include "HashTable.h"

HashValue* FromString(char* hash) {
	HashValue* result = NULL;
	int		   sum    = 0;

	// Hash the input string.
	while (*hash != '\0') sum += (int)*hash;
	sum *= sum;

	// Get the finite size.
	sum %= HASH_ARRAY_SIZE;

	// Allocate the hash item.
	result = (HashValue*)malloc(sizeof(HashValue));
	result->hash_low  |= sum;
	result->hash_high |= sum >> 16;

	return (result);
}

int HashTableInsert(HashTable* table, HashItem* item) {

}

HashItem* HashTableRemove(HashTable* table, HashValue* key);

int HashTableSize(HashTable* table) {
	if (NULL == table) return (0);
	return (table->num_of_items);
}

HashItem* HashTableGet(HashTable* table, HashValue* key) {

}

void HashTableClear(HashTable* table) {

}

#endif // __HASH_TABLE_C__