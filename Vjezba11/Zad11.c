#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define TABLE_SIZE 11

// struktura grada (bst)
typedef struct City {
    char name[MAX];        // ime grada
    int population;        // broj stanovnika
    struct City* left;     // lijevo dijete
    struct City* right;    // desno dijete
} City;

// struktura drzave (vezana lista u hash tablici)
typedef struct Country {
    char name[MAX];        // ime drzave
    City* cities;          // korijen stabla gradova
    struct Country* next;  // sljedeca drzava u listi
} Country;

// kreiranje novog grada
City* createCity(char* name, int population) {
    City* city = (City*)malloc(sizeof(City));
    strcpy(city->name, name);
    city->population = population;
    city->left = NULL;
    city->right = NULL;
    return city;
}

// ubacivanje grada u bst
// sortira se po broju stanovnika, a zatim po nazivu
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
        printf("      %s (%d)\n", root->name, root->population);
        printCities(root->right);
    }
}

// ispis gradova s vise stanovnika od zadanog broja
void searchCities(City* root, int minPop) {
    if (root != NULL) {
        searchCities(root->left, minPop);
        if (root->population > minPop)
            printf("      %s (%d)\n", root->name, root->population);
        searchCities(root->right, minPop);
    }
}

// kreiranje nove drzave
Country* createCountry(char* name) {
    Country* country = (Country*)malloc(sizeof(Country));
    strcpy(country->name, name);
    country->cities = NULL;
    country->next = NULL;
    return country;
}

// hash funkcija
// zbraja ascii vrijednosti prvih pet slova naziva drzave
int hashFunction(char* countryName) {
    int sum = 0;
    for (int i = 0; i < 5 && countryName[i] != '\0'; i++)
        sum += (int)countryName[i];

    return sum % TABLE_SIZE;
}

// ubacivanje drzave u hash tablicu
// kolizije se rjesavaju vezanom listom sortiranom po nazivu
void insertCountryHash(Country* hashTable[], char* name) {
    int index = hashFunction(name);
    Country* newCountry = createCountry(name);

    if (hashTable[index] == NULL ||
        strcmp(name, hashTable[index]->name) < 0) {
        newCountry->next = hashTable[index];
        hashTable[index] = newCountry;
        return;
    }

    Country* temp = hashTable[index];
    while (temp->next != NULL && strcmp(temp->next->name, name) < 0)
        temp = temp->next;

    newCountry->next = temp->next;
    temp->next = newCountry;
}

// ucitavanje gradova iz datoteke
void loadCities(Country* country, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char cityName[MAX];
    int population;

    while (fscanf(file, " %[^,],%d", cityName, &population) == 2)
        country->cities = insertCity(country->cities, cityName, population);

    fclose(file);
}

// ispis cijele hash tablice
void printHashTable(Country* hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("\nhash[%d]:\n", i);

        Country* temp = hashTable[i];
        while (temp != NULL) {
            printf("   %s\n", temp->name);
            printCities(temp->cities);
            temp = temp->next;
        }
    }
}

int main() {
    Country* hashTable[TABLE_SIZE] = { NULL };

    FILE* file = fopen("drzave.txt", "r");
    if (!file) {
        printf("greska pri otvaranju datoteke!\n");
        return 1;
    }

    char countryName[MAX];
    char cityFile[MAX];

    while (fscanf(file, " %s %s", countryName, cityFile) == 2) {
        insertCountryHash(hashTable, countryName);

        int index = hashFunction(countryName);
        Country* temp = hashTable[index];

        while (temp != NULL && strcmp(temp->name, countryName) != 0)
            temp = temp->next;

        if (temp != NULL)
            loadCities(temp, cityFile);
    }

    fclose(file);

    printHashTable(hashTable);

    return 0;
}
