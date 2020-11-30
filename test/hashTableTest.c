#include "../src/hashTable.h"
#include <stdio.h>
#include <stdlib.h>

void printItem(void* item) {
    printf("%i, ", *(int*)item);
}

void printTable(hashTable* ht) {
    iterateTableItems(ht, printItem);
    puts("");
}

int main() {

    hashTable* ht = createHashTable(hashInteger, intComparator);

    for (int i = 0; i < 10; i++) {
        int* nump = malloc(sizeof(int));
        *nump = i;
        addItem(ht, nump);
    }
    printTable(ht);
    int itemToRemove = 5;
    removeTableItem(ht, &itemToRemove) ? printf("Removed: %i\n", itemToRemove) : printf("Failed to remove %i\n", itemToRemove);

    printTable(ht);
    clearTable(ht);
    iterateTableItems(ht, printItem);
    freeHashTable(ht);
}