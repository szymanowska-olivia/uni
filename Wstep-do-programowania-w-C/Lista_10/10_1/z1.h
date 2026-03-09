#ifndef Z1_H
#define Z1_H

#include <stdbool.h>

typedef struct Node {
    int column;
    int row;
    bool atak;
    int kol_atak;
    bool udane;
    struct Node **dzieci; 
    int ile_dzieci;
} Node;


Node *create_node(int column, int row, bool atak, int kol_atak, bool udane);
void dod_dziecko(Node *parent, Node *child);
void free_drzewo(Node *root);

void print_drzewo(Node *root, int depth);

void solve_n_queens(Node *root, int n);

#endif
