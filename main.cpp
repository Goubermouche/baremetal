#include <stdio.h>
#include <stdlib.h>
#include "keywords.h"

int main(void) {
    const char *test_strings[] = {
        "apple", "banana", "cherry", "date",
        "fig", "grape", "kiwi", "lemon",
        "mango", "orange", "unknown"
    };

    for (int i = 0; i < sizeof(test_strings)/sizeof(test_strings[0]); i++) {
        const struct Keyword *k = my_lookup_function(test_strings[i], strlen(test_strings[i]));
        if (k) {
            printf("String '%s' maps to %d\n", test_strings[i], k->value);
        } else {
            printf("String '%s' not found\n", test_strings[i]);
        }
    }

    return 0;
}
