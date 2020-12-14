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

unsigned int intHash(void* val);
unsigned int strHash(void* str);
hashTable* createHashTable(unsigned int (*hashFunction)(void*), bool (*comparator)(void*, void*));
bool addTableItem(hashTable* ht, void* item);
void addTableItems(hashTable* ht, int args, ...);
void* removeTableItem(hashTable* ht, void* item);
bool tableContains(hashTable* ht, void* key);
void iterateTableItems(hashTable* ht, void (*iterator)(void*));
void* getValue(hashTable* ht, void* key);
bool isEmpty(hashTable* ht);
void clearTable(hashTable* ht, bool freeValues);
void freeTable(hashTable* ht, bool freeValues);
void printIntTable(hashTable* ht);
void printStrTable(hashTable* ht);
#endif