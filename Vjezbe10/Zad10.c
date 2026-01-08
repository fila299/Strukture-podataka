#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// struktura grada (bst)
typedef struct City {
    char name[MAX];          // ime grada
    int population;          // broj stanovnika
    struct City* left;       // lijevo dijete
    struct City* right;      // desno dijete
} City;

// struktura drzave (vezana lista)
typedef struct Country {
    char name[MAX];          // ime drzave
    City* cities;            // korijen stabla gradova
    struct Country* next;    // sljedeca drzava u listi
} Country;

// kreiranje grada
City* createCity(char* name, int population) {
    City* city = (City*)malloc(sizeof(City));
    strcpy(city->name, name);
    city->population = population;
    city->left = NULL;
    city->right = NULL;
    return city;
}

// insert grada u bst
// prvo po broju stanovnika, ako je isti onda po imenu
City* insertCity(City* root, char* name, int population) {
    if (root == NULL)
        return createCity(name, population);

    if (population < root->population ||
        (population == root->population && strcmp(name, root->name) < 0))
        root->left = insertCity(root->left, name, population);
    else
        root->right = insertCity(root->right, name, population);

    return root;
}

// inorder ispis gradova
void printCities(City* root) {
    if (root != NULL) {
        printCities(root->left);
        printf("   %s (%d)\n", root->name, root->population);
        printCities(root->right);
    }
}

// ispis gradova s vecim brojem stanovnika od zadanog
void searchCities(City* root, int minPop) {
    if (root != NULL) {
        searchCities(root->left, minPop);
        if (root->population > minPop)
            printf("   %s (%d)\n", root->name, root->population);
        searchCities(root->right, minPop);
    }
}

// kreiranje drzave
Country* createCountry(char* name) {
    Country* country = (Country*)malloc(sizeof(Country));
    strcpy(country->name, name);
    country->cities = NULL;
    country->next = NULL;
    return country;
}

// sortirani insert drzave u vezanu listu
Country* insertCountry(Country* head, char* name) {
    Country* newCountry = createCountry(name);

    if (head == NULL || strcmp(name, head->name) < 0) {
        newCountry->next = head;
        return newCountry;
    }

    Country* temp = head;
    while (temp->next != NULL && strcmp(temp->next->name, name) < 0)
        temp = temp->next;

    newCountry->next = temp->next;
    temp->next = newCountry;

    return head;
}

// ucitavanje gradova iz datoteke
void loadCities(Country* country, char* filename) {
    FILE* file = fopen(drzave.txt, "r");
    if (!file) return;

    char cityName[MAX];
    int population;

    while (fscanf(file, " %[^,],%d", cityName, &population) == 2) {
