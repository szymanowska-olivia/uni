
#include "z1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "błąd");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "błąd");
        return 1;
    }

    Node *root = create_node(-1, -1, false, -1, false);
    solve_n_queens(root, n);
    print_drzewo(root, 0);
    free_drzewo(root);

    return 0;
}
