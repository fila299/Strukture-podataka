#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;              // vrijednost u čvoru
    struct Node* left;      // pokazivač na lijevo dijete
    struct Node* right;     // pokazivač na desno dijete
} Node;

// funkcija koja stvara novi čvor
Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));  // zauzimamo memoriju
    node->value = value;                       // spremamo vrijednost
    node->left = NULL;                         // na početku nema djece
    node->right = NULL;
    return node;                               // vraćamo novi čvor
}

// a) insert – dodavanje elementa u bst
Node* insert(Node* root, int value) {
    // ako je stablo prazno, novi čvor postaje korijen
    if (root == NULL)
        return createNode(value);

    // ako je manji ide lijevo
    if (value < root->value)
        root->left = insert(root->left, value);
    // ako je veći ili jednak ide desno
    else
        root->right = insert(root->right, value);

    // uvijek vraćamo korijen stabla
    return root;
}

// inorder prolazak – koristi se za ispis u datoteku
void inorder(Node* root, FILE* file) {
    if (root != NULL) {
        inorder(root->left, file);         // lijevo podstablo
        fprintf(file, "%d ", root->value); // ispis trenutnog čvora
        inorder(root->right, file);        // desno podstablo
    }
}

// b) replace – zamjena vrijednosti čvora sumom njegovih potomaka
int replace(Node* root) {
    // ako nema čvora, suma je 0
    if (root == NULL)
        return 0;

    // prvo računamo lijevo i desno podstablo
    int leftSum = replace(root->left);
    int rightSum = replace(root->right);

    // pamtimo staru vrijednost
    int oldValue = root->value;

    // novu vrijednost postavljamo kao zbroj potomaka
    root->value = leftSum + rightSum;

    // vraćamo ukupnu sumu podstabla (stara + nova)
    return oldValue + root->value;
}

int main() {
    Node* root = NULL;     // na početku nemamo stablo
    int n = 10;            // broj elemenata
    int value;

    srand((unsigned)time(NULL));  // inicijalizacija rand()

    // c) random
    for (int i = 0; i < n; i++) {
        value = rand() % 81 + 10;   // 10 – 90
        root = insert(root, value); // dodavanje u stablo
    }

    // otvaranje datoteke za pisanje
    FILE* file = fopen("ispis.txt", "w");
    if (file == NULL) {
        printf("greska pri otvaranju datoteke.\n");
        return 1;
    }

    // inorder ispis nakon insert
    fprintf(file, "Inorder nakon insert:\n");
    inorder(root, file);
    fprintf(file, "\n");

    // poziv replace funkcije
    replace(root);

    // inorder ispis nakon replace
    fprintf(file, "Inorder nakon replace:\n");
    inorder(root, file);

    fclose(file);  // zatvaranje datoteke

    printf("podaci su upisani u output.txt\n");
    return 0;
}
