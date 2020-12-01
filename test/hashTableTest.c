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
    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int len = sizeof(nums) / sizeof(int);
    for (int i = 0; i < len; i++) {
        addTableItem(ht, &nums[i]);
    }
    printTable(ht);
    int itemToRemove = 5;
    removeTableItem(ht, &itemToRemove) ? printf("Removed: %i\n", itemToRemove) : printf("Failed to remove %i\n", itemToRemove);

    printTable(ht);
    clearTable(ht, false);
    iterateTableItems(ht, printItem);
    freeTable(ht, false);
}