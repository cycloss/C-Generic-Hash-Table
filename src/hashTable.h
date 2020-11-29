#ifndef LINKED_LIST
#define LINKED_LIST
#include <linkedList.h>
#endif

#include <stdbool.h>

//TODO fix the fact that linked list nodes are declared twice

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
bool addItem(hashTable* ht, void* item);
void clear(hashTable* s);
bool removeItem(void* item);
bool contains(hashTable* s, void* key);
void* getValue(hashTable* s, void* key);
bool isEmpty(hashTable* s);
void freeSet(hashTable* s);
