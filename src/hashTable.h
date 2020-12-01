#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <linkedList.h>
#include <stdbool.h>

typedef struct {
    int _bucketCount;
    int _itemCount;
    int (*_hashFunction)(void*);
    bool (*_comparator)(void*, void*);
    linkedList** table;
} hashTable;

typedef struct {
    void* key;
    void* value;
} tableItem;

int hashInteger(void* val);
hashTable* createHashTable(int (*hashFunction)(void*), bool (*comparator)(void*, void*));
bool addTableItem(hashTable* ht, void* item);
bool removeTableItem(hashTable* ht, void* item);
bool tableContains(hashTable* ht, void* key);
void iterateTableItems(hashTable* ht, void (*iterator)(void*));
void* getValue(hashTable* ht, void* key);
bool isEmpty(hashTable* ht);
void clearTable(hashTable* ht, bool freeValues);
void freeTable(hashTable* ht, bool freeValues);

#endif