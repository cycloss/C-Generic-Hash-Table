#ifndef LINKED_LIST
#define LINKED_LIST
#include <linkedList.h>
#endif

#include "hashTable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//TODO make hashtable dynamic
// #define GROWTH_FACTOR 2
// #define LOAD_FACTOR 0.75
#define a 1664525
#define c 1013904223
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
int hashInteger(void* val) {
    return (a * *(int*)val + c) % SIZE;
}

//TODO change hashfunc to accept void pointer
hashTable* createHashTable(int (*hashFunction)(void*), bool (*comparator)(void*, void*)) {
    hashTable* ht = malloc(sizeof(hashTable));
    linkedList** buckets = malloc(sizeof(linkedList*) * SIZE);
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
    nullCheck(ht);
    int index = ht->_hashFunction(item);
    linkedList* l = ht->table[index];
    if (!l) {
        l = ht->table[index] = createList();
    }
    appendToList(l, item);
}

void clear(hashTable* s) {
}

bool removeItem(void* item) {
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
}

void freeSet(hashTable* s) {
}
