#include "z1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Node *create_node(int column, int row, bool atak, int kol_atak, bool udane) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->column = column;
    node->row = row;
    node->atak = atak;
    node->kol_atak = kol_atak;
    node->udane = udane;
    node->dzieci = NULL;
    node->ile_dzieci = 0;
    return node;
}

void dod_dziecko(Node *parent, Node *child) {
    parent->ile_dzieci++;
    parent->dzieci = (Node **)realloc(parent->dzieci, sizeof(Node *) * parent->ile_dzieci);
    parent->dzieci[parent->ile_dzieci - 1] = child;
}

void print_drzewo(Node *root, int depth) {
    for (int i = 0; i < depth; i++) {
        if (i < depth - 1) printf("| ");
        else printf("%s", root->atak ? "+-- " : "+-\\ ");
    }

    if (root->column != -1) {
         if (root->atak) 
            printf(" Kolumna %d wiersz %d jest atakowany przez hetmana z kolumny %d\n", root->column, root->row, root->kol_atak);
    else if (root->udane)
            printf(" Kolumna %d wiersz %d nie jest atakowany, stawiamy hetmana - SUKCES!\n", root->column, root->row);
    else
            printf(" Kolumna %d wiersz %d nie jest atakowany, stawiamy hetmana\n", root->column, root->row);
    }

    for (int i = 0; i < root->ile_dzieci; i++) print_drzewo(root->dzieci[i], depth + 1);
}

void free_drzewo(Node *root) {
    for (int i = 0; i < root->ile_dzieci; i++) free_drzewo(root->dzieci[i]);
    free(root->dzieci);
    free(root);
}

int is_attacked(int *queens, int column, int row) {
    for (int i = 0; i < column; i++) {
        if (queens[i] == row || abs(queens[i] - row) == abs(i - column)) return i; 
    }
    return -1; 
}

void rek(Node *node, int *queens, int column, int n) {
    if (column == n) {
        node->udane = true;
        return;
    }

    for (int row = 0; row < n; row++) {
        int kol_atak = is_attacked(queens, column, row);
        bool atak = (kol_atak != -1);
        Node *child = create_node(column, row, atak, kol_atak, false);
        dod_dziecko(node, child);

        if (!atak) {
            queens[column] = row;
            rek(child, queens, column + 1, n);
        }
    }
}

void solve_n_queens(Node *root, int n) {
    int *queens = (int *)malloc(sizeof(int) * n);
    rek(root, queens, 0, n);
    free(queens);
}
