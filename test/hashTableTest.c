#include "../src/hashTable.h"
#include "hashTableTest.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    hashTable* ht = createHashTable(hashInteger, intComparator);
    int nums[80];
    for (int i = 0; i < len(nums); i++) {
        nums[i] = i + 1;
        addTableItem(ht, &nums[i]);
    }
    for (int i = 0; i < len(nums); i++) {
        addTableItem(ht, &nums[i]);
    }
    int rejectCount = 0;
    for (int i = 0; i < len(nums); i++) {
        if (!addTableItem(ht, &nums[i])) {
            rejectCount++;
        }
    }
    printf("Duplicate reject count: %d\n", rejectCount);

    printIntTable(ht);
    int itemToRemove = 5;
    removeTableItem(ht, &itemToRemove) ? printf("Removed: %i\n", itemToRemove) : printf("Failed to remove %i\n", itemToRemove);

    printIntTable(ht);
    freeTable(ht, false);

    hashTable* ht2 = createHashTable(hashString, stringComparator);
    char* strs[] = { "a", "b", "aba", "aab" };

    for (int i = 0; i < len(strs); i++) {
        addTableItem(ht2, strs[i]);
    }

    printStrTable(ht2);
    freeTable(ht2, false);
}

void printIntItem(void* item) {
    printf("%i, ", *(int*)item);
}

void printIntTable(hashTable* ht) {
    iterateTableItems(ht, printIntItem);
    puts("");
}

void printStrItem(void* item) {
    printf("%s, ", (char*)item);
}

void printStrTable(hashTable* ht) {
    iterateTableItems(ht, printStrItem);
    puts("");
}