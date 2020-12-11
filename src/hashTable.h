#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <linkedList.h>
#include <stdbool.h>

typedef struct {
    int _bucketCount;
    int _itemCount;
    unsigned int (*_hashFunction)(void*);
    bool (*_comparator)(void*, void*);
    linkedList** table;
} hashTable;

typedef struct {
    void* key;
    void* value;
} tableItem;

unsigned int hashInteger(void* val);
unsigned int hashString(void* str);
hashTable* createHashTable(unsigned int (*hashFunction)(void*), bool (*comparator)(void*, void*));
bool addTableItem(hashTable* ht, void* item);
void* removeTableItem(hashTable* ht, void* item);
bool tableContains(hashTable* ht, void* key);
void iterateTableItems(hashTable* ht, void (*iterator)(void*));
void* getValue(hashTable* ht, void* key);
bool isEmpty(hashTable* ht);
void clearTable(hashTable* ht, bool freeValues);
void freeTable(hashTable* ht, bool freeValues);

#endif