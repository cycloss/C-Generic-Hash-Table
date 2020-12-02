#include "hashTable.h"
#include <linkedList.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//TODO write readme
//TODO make hashtable dynamic
// #define GROWTH_FACTOR 2
// #define LOAD_FACTOR 0.75

//TODO make string hashing function
//TODO make example of custom hashing function in example

#define a 214013
#define c 2531011
#define SIZE 1000

//simple linear congruental generator for pseudo random numbers
//uses microsoft visual's values for a and c.
//Good for even spread but not good for true random behaviour as almost perfectly periodic
int hashInteger(void* val) {
    return (int)((a * *(unsigned int*)val + c) % SIZE);
}

static int stringLength(char* str) {
    int len = 0;
    for (char ch = *str; ch != '\0'; str++, ch = *str, len++)
        ;
    return len;
}

int hashString(void* str) {
    char* strCasted = (char*)str;
    unsigned int fullHash = 0;
    unsigned int previousCharHash = 7;
    int len = stringLength(strCasted);
    for (int i = 0; i < len; i++) {
        unsigned int hash = hashInteger(&strCasted[i]);
        fullHash += hash * previousCharHash;
        previousCharHash = hash;
    }
    return fullHash % SIZE;
}

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

bool addTableItem(hashTable* ht, void* item) {
    int index = ht->_hashFunction(item);
    linkedList* l = ht->table[index];
    if (!l) {
        l = ht->table[index] = createList();
    }
    appendToList(l, item);
    ht->_itemCount++;
    return l;
}

void iterateTableItems(hashTable* ht, void (*iterator)(void*)) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        linkedList* bucket = ht->table[i];
        if (bucket) {
            iterateListValues(bucket, iterator);
        }
    }
}

void clearTable(hashTable* ht, bool freeValues) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        linkedList* bucket = ht->table[i];
        if (bucket) {
            freeList(bucket, freeValues);
            ht->table[i] = NULL;
        }
    }
    ht->_itemCount = 0;
}

void freeTable(hashTable* ht, bool freeValues) {
    clearTable(ht, freeValues);
    free(ht->table);
    free(ht);
}

/**
 * Removes the item from the table. Does not call free on the item removed.
 * @return pointer to the item if successful, NULL if table did not contain item.
 **/
void* removeTableItem(hashTable* ht, void* item) {
    int hashedInd = ht->_hashFunction(item);
    linkedList* l = ht->table[hashedInd];
    if (l) {
        void* removed = removeValue(l, item, ht->_comparator);
        if (removed) {
            ht->_itemCount--;
            return removed;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

bool tableContains(hashTable* ht, void* key) {
    int hashedInd = ht->_hashFunction(key);
    linkedList* l = ht->table[hashedInd];
    if (l) {
        int index = findIndexOfValue(l, key, ht->_comparator);
        return index != -1;
    } else {
        return false;
    }
}

void* getValue(hashTable* ht, void* key) {
    int hashedInd = ht->_hashFunction(key);
    linkedList* l = ht->table[hashedInd];
    if (l) {
        int index = findIndexOfValue(l, key, ht->_comparator);
        return index == -1 ? NULL : getValueAt(l, index);
    } else {
        return NULL;
    }
}

bool isEmpty(hashTable* ht) {
    return ht->_itemCount == 0;
}
