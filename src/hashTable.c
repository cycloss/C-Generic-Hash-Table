#include "hashTable.h"
#include <linkedList.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//TODO make hashtable dynamic
// #define GROWTH_FACTOR 2
// #define LOAD_FACTOR 0.75
#define a 214013
#define c 2531011
#define SIZE 1000

static void fatalError(char* msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
}

static void nullCheck(hashTable* s) {
    if (!s) {
        fatalError("hashTable was null");
    }
}

//simple linear congruental generator for pseudo random numbers
//uses microsoft visual's values for a and c.
//Good for even spread but not good for true random behaviour as almost perfectly periodic
int hashInteger(void* val) {
    return (int)((a * *(unsigned int*)val + c) % SIZE);
}

//TODO change hashfunc to accept void pointer
hashTable* createHashTable(int (*hashFunction)(void*), bool (*comparator)(void*, void*)) {
    hashTable* ht = malloc(sizeof(hashTable));
    linkedList** buckets = malloc(sizeof(linkedList*) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        buckets[i] = NULL;
    }
    *ht = (hashTable) {
        SIZE,
        0,
        hashFunction,
        comparator,
        buckets
    };
    return ht;
}

bool addItem(hashTable* ht, void* item) {
    int index = ht->_hashFunction(item);
    linkedList* l = ht->table[index];
    if (!l) {
        l = ht->table[index] = createList();
    }
    appendToList(l, item);
    ht->_itemCount++;
}

void iterateTableItems(hashTable* ht, void (*iterator)(void*)) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        linkedList* bucket = ht->table[i];
        if (bucket) {
            iterateListValues(bucket, iterator);
        }
    }
}

void clearTable(hashTable* ht) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        linkedList* bucket = ht->table[i];
        if (bucket) {
            freeList(bucket);
            ht->table[i] = NULL;
        }
    }
    ht->_itemCount = 0;
}

void freeHashTable(hashTable* ht) {
    clearTable(ht);
    free(ht->table);
    free(ht);
}

bool removeTableItem(hashTable* ht, void* item) {
    int hashedInd = ht->_hashFunction(item);
    linkedList* l = ht->table[hashedInd];
    if (l) {
        void* removed = removeValue(l, item, ht->_comparator);
        if (removed) {
            free(removed);
            ht->_itemCount--;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool contains(hashTable* s, void* key) {
    nullCheck(s);
    int hashedInd = s->_hashFunction(key);
    linkedList* l = s->table[hashedInd];
    if (l) {
        int index = findIndexOfValue(l, key, s->_comparator);
        return index != -1;
    } else {
        return false;
    }
}

void* getValue(hashTable* s, void* key) {
    nullCheck(s);
    int hashedInd = s->_hashFunction(key);
    linkedList* l = s->table[hashedInd];
    if (l) {
        int index = findIndexOfValue(l, key, s->_comparator);
        return index == -1 ? NULL : getValueAt(l, index);
    } else {
        return NULL;
    }
}

bool isEmpty(hashTable* s) {
    return s->_itemCount == 0;
}
