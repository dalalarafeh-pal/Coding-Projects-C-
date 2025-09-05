#include "hash.h"
#include <stdio.h>
#include <string.h>


int main() {
    Hashtable *h = hash_create();

    char line[255];
    int i = 0;

    while (fgets(line, sizeof(line), stdin)) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        if (!hash_get(h, line)) {
            hash_put(h, line, 1);
            i++;
        }
    }

    printf("%d\n", i);
    hash_destroy(&(*h));

    return 0;
}

