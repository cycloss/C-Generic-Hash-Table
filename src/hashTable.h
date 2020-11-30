#include <linkedList.h>
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
void clearTable(hashTable* ht);
bool removeTableItem(hashTable* ht, void* item);
bool contains(hashTable* ht, void* key);
void iterateTableItems(hashTable* ht, void (*iterator)(void*));
void* getValue(hashTable* ht, void* key);
bool isEmpty(hashTable* ht);
void freeHashTable(hashTable* ht);
