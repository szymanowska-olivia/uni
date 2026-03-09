/*Chcielibyśmy zakodować pewien tekst przy pomocy kodowania Huffmana (https://pl.wikipedia.org/wiki/Kodowanie_Huffmana). Drzewo będziemy generować z podanych na wejściu 26 liczb odpowiadających spodziewanej częstotliwości kolejnych liter alfabetu. Tekst dany jest w postaci ciągu małych liter alfabetu angielskiego.

Przy generowaniu drzewa należy korzystać z następujących zasad:
- na początku sortujemy litery malejąco po spodziewanych częstotliwościach (jeśli dwie litery mają te same częstotliwości, ich kolejność powinna być alfabetyczna) i tworzymy jednoelementowe drzewa.
- nowe drzewo zawsze generujemy z dwóch ostatnich na liście, ostatni element zostaje prawym poddrzewem nowego drzewa, a przedostatni lewym. To drzewo jest teraz ostatnie na liście
- przesuwamy ostatnie drzewo na liście w lewo tak długo, aż lista drzew nie będzie posortowana po częstotliwościach (jeśli na liście pojawią się dwie równe częstotliwości w węzłach drzewa, nie należy ich zamieniać).
Dodatkowo w kodowaniu lewe poddrzewo odpowiada znakowi 0 a prawe 1.

Wejście:
W pierwszej linii wejścia znajduje się 26 liczb naturalnych, co najmniej 2 dodatnie (możesz założyć, że ich suma mieści się w typie danych int) odpowiadających spodziewanym częstotliwościom wystąpienia kolejnych liter alfabetu angielskiego. W drugiej linii wejścia znajduje się liczba naturalna n ≤ 106. Trzecia linia wejścia składa się z n małych liter alfabetu angielskiego (możesz założyć, że tylko tych liter, które miały niezerowe częstotliwości).

Wyjście:
Na wyjściu powinien znaleźć się ciąg zer i jedynek odpowiadający zakodowanej wiadomości.

Przykłady:
A
Wejście:

12 7 0 0 0 0 0 0 0 0 0 0 0 6 0 0 0 0 0 0 0 0 0 0 0 0
6
abnnab

Wyjście:

1000101100

B
Wejście:

1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
4
abcd

Wyjście:

10110001

C
Wejście:

12 2 0 0 0 0 0 0 0 0 0 0 0 6 0 0 0 0 0 0 0 0 0 0 0 0
6
abnnab

Wyjście:

0111010011*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char lit;
    int fq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node **trees;
    int size;
} List;

int compare(const void *a, const void *b) {
    Node *nodeA = *(Node **)a;
    Node *nodeB = *(Node **)b;
    return nodeB->fq - nodeA->fq;
}

Node* create_node(char lit, int fq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->lit = lit;
    node->fq = fq;
    node->left = node->right = NULL;
    return node;
}

Node* tree(int f[]) {
    List list;
    list.trees = (Node**)malloc(26 * sizeof(Node*));
    list.size = 0;

    for (int i = 0; i < 26; i++) {
        if (f[i] > 0) list.trees[list.size++] = create_node('a' + i, f[i]);
    }
    qsort(list.trees, list.size, sizeof(Node *), compare);

    while (list.size > 1) {
        Node *left = list.trees[list.size - 2];
        Node *right = list.trees[list.size - 1];
        Node *new_node = create_node('\0', left->fq + right->fq);
        new_node->left = left;
        new_node->right = right;

        list.size -= 2;
        list.trees[list.size++] = new_node;
        
        qsort(list.trees, list.size, sizeof(Node *), compare);
    }

    Node *root = list.trees[0];
    free(list.trees);
    return root;
}

void Huffman(Node *root, char *code, int depth, char **codes) {
    if (root == NULL) return;

    if (root->lit != '\0') {
        code[depth] = '\0';


        codes[root->lit - 'a'] = (char*)malloc((depth + 1) * sizeof(char));
        strcpy(codes[root->lit - 'a'], code);
    }

    code[depth] = '0';
    Huffman(root->left, code, depth + 1, codes);
    code[depth] = '1';
    Huffman(root->right, code, depth + 1, codes);
}



void kod(char *mes, char **codes) {
    for (int i = 0; mes[i] != '\0'; i++) printf("%s", codes[mes[i] - 'a']);
    printf("\n");
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    int f[26];
    for (int i = 0; i < 26; i++) scanf("%d", &f[i]);

    int ilen;
    scanf("%d", &ilen);
    char mes[ilen + 1];
    scanf("%s", mes);
    Node *root = tree(f);

    char *codes[26] = {NULL};
    char code[26];
    Huffman(root, code, 0, codes);
    // printf("og: %s\n", mes);
    kod(mes, codes);

    for (int i = 0; i < 26; i++) {
        if (codes[i] != NULL) free(codes[i]);
    }
    free_tree(root);

    return 0;
}