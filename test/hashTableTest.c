
#include "../src/hashTable.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    hashTable* ht = createHashTable(hashInteger, intComparator);

    for (int i = 0; i < 10; i++) {
        int* nump = malloc(sizeof(int));
        *nump = i;
        addItem(ht, nump);
    }

    for (int i = 0; i < 20; i++) {
        bool hasVal = contains(ht, &i);
        if (hasVal) {
            puts("Val present");
        } else {
            puts("Val not present");
        }
    }
}