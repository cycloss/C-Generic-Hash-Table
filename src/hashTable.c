#include "hashTable.h"
#include <linkedList.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//TODO write readme
//TODO reorder functions

// Factor representing the number of items currently held in the table as a proportion of total table size, past which the table will expand by GROWTH_FACTOR
#define LOAD_FACTOR 0.75
// Factor which table size will be multiplied by when it passes LOAD_FACTOR
#define GROWTH_FACTOR 2

//TODO make example of custom hashing function in example

#define a 214013
#define c 2531011
#define INITIAL_SIZE 1000

static void fatalError(char* msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
}

/**simple linear congruental generator for pseudo random numbers.
* uses microsoft visual's values for a and c.
* Good for even spread but not good for true random behaviour as almost perfectly periodic.
* @param pointer to integer to be hashed 
**/
static int generateRand(int seed) {
    return (int)(a * (unsigned int)seed + c);
}

unsigned int hashInteger(void* num) {
    return generateRand(*(int*)num);
}

static int stringLength(char* str) {
    int len = 0;
    for (char ch = *str; ch != '\0'; ch = *++str, len++)
        ;
    return len;
}

unsigned int hashString(void* str) {
    char* strCasted = (char*)str;
    unsigned int fullHash = 0;
    unsigned int previousCharHash = 7;
    int len = stringLength(strCasted);
    for (int i = 0; i < len; i++) {
        unsigned int hash = generateRand(strCasted[i]);
        fullHash += hash * previousCharHash;
        previousCharHash = hash;
    }
    return fullHash;
}

static int generateTableHash(unsigned int rawHash, int tableSize) {
    return rawHash % tableSize;
}

hashTable* createHashTable(unsigned int (*hashFunction)(void*), bool (*comparator)(void*, void*)) {
    hashTable* ht = malloc(sizeof(hashTable));
    linkedList** buckets = malloc(sizeof(linkedList*) * INITIAL_SIZE);
    for (int i = 0; i < INITIAL_SIZE; i++) {
        buckets[i] = NULL;
    }
    *ht = (hashTable) {
        INITIAL_SIZE,
        0,
        hashFunction,
        comparator,
        buckets
    };
    return ht;
}

static void rehashTable(hashTable* ht, linkedList** newTable, int newSize) {
    for (int i = 0; i < ht->_bucketCount; i++) {
        linkedList* bucket = ht->table[i];
        if (bucket) {
            for (void* removed = removeFirst(bucket); removed; removed = removeFirst(bucket)) {
                int newHash = generateTableHash(ht->_hashFunction(removed), newSize);
                linkedList* l = newTable[newHash];
                if (!l) {
                    l = newTable[newHash] = createList();
                }
                appendToList(l, removed);
            }
            free(bucket);
        }
    }
}

static void expandHashTable(hashTable* ht) {
    int newSize = ht->_bucketCount * GROWTH_FACTOR;
    linkedList** newTable = malloc(sizeof(linkedList*) * newSize);
    if (!newTable) {
        fatalError("Failed to expand hash table");
    }
    printf("Expanding hash table from %i to %i\n", ht->_bucketCount, newSize);
    rehashTable(ht, newTable, newSize);
    free(ht->table);
    ht->table = newTable;
    ht->_bucketCount = newSize;
}

bool addTableItem(hashTable* ht, void* item) {
    int index = generateTableHash(ht->_hashFunction(item), ht->_bucketCount);
    linkedList* l = ht->table[index];
    if (!l) {
        l = ht->table[index] = createList();
    } else if (findIndexOfValue(l, item, ht->_comparator) != -1) {
        return false;
    }
    appendToList(l, item);
    float newItemCount = (float)++ht->_itemCount;
    if ((newItemCount / ht->_bucketCount) > LOAD_FACTOR) {
        expandHashTable(ht);
    }
    return l;
}

void addTableItems(hashTable* ht, int args, ...) {
    va_list ls;
    va_start(ls, args);
    for (int i = 0; i < args; i++) {
        addTableItem(ht, va_arg(ls, void*));
    }
    va_end(ls);
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
    int hashedInd = generateTableHash(ht->_hashFunction(item), ht->_bucketCount);
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
    int hashedInd = generateTableHash(ht->_hashFunction(key), ht->_bucketCount);
    linkedList* l = ht->table[hashedInd];
    if (l) {
        int index = findIndexOfValue(l, key, ht->_comparator);
        return index != -1;
    } else {
        return false;
    }
}

void* getValue(hashTable* ht, void* key) {
    int hashedInd = generateTableHash(ht->_hashFunction(key), ht->_bucketCount);
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

static void printIntItem(void* item) {
    printf("%i\n", *(int*)item);
}

void printIntTable(hashTable* ht) {
    iterateTableItems(ht, printIntItem);
    puts("");
}

static void printStrItem(void* item) {
    printf("%s\n", (char*)item);
}

void printStrTable(hashTable* ht) {
    iterateTableItems(ht, printStrItem);
    puts("");
}