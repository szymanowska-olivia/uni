#include "funkcje.h"
#include <stdlib.h>

// Funkcja do sortowania wierszy
void sort_w(char ***w, size_t lw, int (*komparator)(const void *, const void *)) {
#ifdef USE_QSORT
    qsort(w, lw, sizeof(char **), komparator);  // Sortowanie za pomocą qsort
#else
    for (size_t i = 0; i < lw - 1; i++) {  // Sortowanie bąbelkowe
        for (size_t j = 0; j < lw - i - 1; j++) {
            if (komparator(&w[j], &w[j + 1]) > 0) {  // Porównanie dwóch wierszy
                char **pom = w[j];
                w[j] = w[j + 1];
                w[j + 1] = pom;
            }
        }
    }
#endif
}

