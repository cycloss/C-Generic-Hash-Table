#include "../src/hashTable.h"

#define len(x) sizeof(x) / sizeof(x[0])

void printIntItem(void* item);
void printIntTable(hashTable* ht);
void printStrItem(void* item);
void printStrTable(hashTable* ht);