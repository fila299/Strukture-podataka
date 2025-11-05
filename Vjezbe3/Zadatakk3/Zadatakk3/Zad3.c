#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_SIZE 50
#define EXIT_SUCCESS 1
#define SCANF_ERROR -1
#define MALLOC_ERROR -2


typedef struct _PersonNode {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    struct _PersonNode* next;
}Person;

Person* createPerson();
int addToListFront(Person* head);
int printList(Person* firstElement);
int addToListEnd(Person* head);
Person* findPersonBySurname(Person* firstElement, char* surname);
int deletePersonBySurname(Person* head, char* surname);
void freeMemory(Person* head);

int insertAfter(Person* firstElement);
int insertBefore(Person* head);
int sortListBySurname(Person* head);
int saveListToFile(Person* firstElement);
int loadListFromFile(Person* head);


int main() {
    
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    char choice = '\0';
    char surnameToFind[MAX_SIZE] = { 0 };

    while (choice != 'x') {
        printf("\n--- GLAVNI IZBORNIK ---\n");
        printf("A. Dodaj na pocetak\n");
        printf("B. Ispisi listu\n");
        printf("C. Dodaj na kraj\n");
        printf("D. Pronadji po prezimenu\n");
        printf("E. Obrisi element\n");
        printf("--- Zadatak 3 ---\n");
        printf("F. Dodaj IZA elementa\n");
        printf("G. Dodaj ISPRED elementa\n");
        printf("H. Sortiraj listu (po prezimenu)\n");
        printf("I. Spremi listu u 'Osobe.txt'\n");
        printf("J. Ucitaj listu iz 'Osobe.txt'\n");
        printf("X. Izlaz\n");
        printf("Vas odabir: ");

        scanf(" %c", &choice);
        choice = tolower(choice);

        switch (choice) {
        case 'a':
            printf("Dodavanje na pocetak: \n");
            addToListFront(&head);
            break;
        case 'b':
            printf("Ispis liste\n");
            printList(head.next);
            break;
        case 'c':
            printf("Dodaj na kraj liste\n");
            addToListEnd(&head);
            break;
        case 'd':
            printf("Pronadi element po prezimenu\n");
            printf("Upisite prezime: ");
            scanf("%s", surnameToFind);

            Person* foundPerson = findPersonBySurname(head.next, surnameToFind);

            if (foundPerson != NULL) {
                printf("Pronadena osoba:\n");
                printf("\tIme:%s, Prezime:%s, Godina:%d\n", foundPerson->name, foundPerson->surname, foundPerson->birthYear);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;
        case 'e':
            printf("Brisanje po prezimenu\n");
            printf("Unesite prezime: ");
            scanf("%s", surnameToFind);
            deletePersonBySurname(&head, surnameToFind);
            break;

          
        case 'f':
            printf("--- Dodavanje IZA elementa ---\n");
            insertAfter(head.next);
            break;
        case 'g':
            printf("--- Dodavanje ISPRED elementa ---\n");
            insertBefore(&head);
            break;
        case 'h':
            printf("--- Sortiranje liste ---\n");
            sortListBySurname(&head);
            printf("Lista je sortirana.\n");
            printList(head.next);
            break;
        case 'i':
            printf("--- Spremanje u datoteku ---\n");
            saveListToFile(head.next);
            break;
        case 'j':
            printf("--- Ucitavanje iz datoteke ---\n");
            loadListFromFile(&head);
            printf("Lista ucitana:\n");
            printList(head.next);
            break;

        case 'x':
            printf("Izlaz\n");
            break;
        default:
            printf("Nepoznat unos. Pokusajte ponovo.\n");
            break;
        }
    }

    freeMemory(&head);
    return 0;
}


Person* createPerson() {
    Person* newPerson = malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("Neuspjesna alokacija memorije!");
        return NULL;
    }

    printf("\tUnesite ime:");
    scanf("%s", newPerson->name);
    printf("\tUnesite prezime:");
    scanf("%s", newPerson->surname);
    printf("\tUnesite godinu rodenja:");
    scanf("%d", &newPerson->birthYear);

    newPerson->next = NULL;
    return newPerson;
}

int addToListFront(Person* head) {
    Person* newPerson = createPerson();
    if (newPerson == NULL) {
        return MALLOC_ERROR;
    }
    newPerson->next = head->next;
    head->next = newPerson;
    return EXIT_SUCCESS;
}

int printList(Person* firstElement) {
    if (firstElement == NULL) {
        printf("Lista je prazna.\n");
        return EXIT_SUCCESS;
    }
    Person* current = firstElement;
    while (current != NULL) {
        printf("\tIme:%s, Prezime:%s, Godina:%d\n",
            current->name,
            current->surname,
            current->birthYear);
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int addToListEnd(Person* head) {
    Person* newPerson = createPerson();
    if (newPerson == NULL) {
        return MALLOC_ERROR;
    }
    Person* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newPerson;
    return EXIT_SUCCESS;
}

Person* findPersonBySurname(Person* firstElement, char* surname) {
    Person* current = firstElement;
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int deletePersonBySurname(Person* head, char* surname) {
    Person* prev = head;
    Person* current = head->next;
    Person* temp = NULL;

    while (current != NULL && strcmp(current->surname, surname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadjena.\n", surname);
        return EXIT_SUCCESS;
    }

    prev->next = current->next;
    temp = current;
    free(temp);

    printf("Osoba '%s' je obrisana.\n", surname);
    return EXIT_SUCCESS;
}

void freeMemory(Person* head) {
    Person* current = head->next;
    Person* temp = NULL;

    printf("Oslobadjam memoriju...\n");
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    head->next = NULL;
    printf("Memorija oslobodjena.\n");
}


int insertAfter(Person* firstElement) {
    char surnameToFind[MAX_SIZE];
    printf("Unesite prezime osobe IZA koje zelite dodati: ");
    scanf("%s", surnameToFind);

    Person* targetNode = findPersonBySurname(firstElement, surnameToFind);

    if (targetNode == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadjena.\n", surnameToFind);
        return SCANF_ERROR;
    }

    printf("Unesite podatke za NOVU osobu:\n");
    Person* newNode = createPerson();
    if (newNode == NULL) {
        return MALLOC_ERROR;
    }

    newNode->next = targetNode->next;
    targetNode->next = newNode;

    printf("Osoba uspjesno dodana.\n");
    return EXIT_SUCCESS;
}

int insertBefore(Person* head) {
    char surnameToFind[MAX_SIZE];
    printf("Unesite prezime osobe ISPRED koje zelite dodati: ");
    scanf("%s", surnameToFind);

    Person* prev = head;
    Person* current = head->next;

    while (current != NULL && strcmp(current->surname, surnameToFind) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadjena.\n", surnameToFind);
        return SCANF_ERROR;
    }

    printf("Unesite podatke za NOVU osobu:\n");
    Person* newNode = createPerson();
    if (newNode == NULL) {
        return MALLOC_ERROR;
    }

    newNode->next = current;
    prev->next = newNode;

    printf("Osoba uspjesno dodana.\n");
    return EXIT_SUCCESS;
}

int sortListBySurname(Person* head) {
    if (head->next == NULL || head->next->next == NULL) {
        return EXIT_SUCCESS;
    }

    int swapped = 0;
    do {
        swapped = 0;
        Person* p = head;
        Person* q = head->next;

        while (q != NULL && q->next != NULL) {
            if (strcmp(q->surname, q->next->surname) > 0) {
                Person* r = q->next;

                q->next = r->next;
                r->next = q;
                p->next = r;

                swapped = 1;
                p = r;
            }
            else {
                p = q;
                q = q->next;
            }
        }
    } while (swapped);

    return EXIT_SUCCESS;
}

int saveListToFile(Person* firstElement) {
    FILE* file = NULL;

    
    file = fopen("Osobe.txt", "w");

    if (file == NULL) {
        printf("Greska: Nije moguce otvoriti datoteku Osobe.txt\n");
        return SCANF_ERROR;
    }

    if (firstElement == NULL) {
        printf("Lista je prazna, nista za spremiti.\n");
        fclose(file);
        return EXIT_SUCCESS;
    }

    Person* current = firstElement;
    while (current != NULL) {
        fprintf(file, "%s %s %d\n",
            current->name,
            current->surname,
            current->birthYear);
        current = current->next;
    }

    fclose(file);
    printf("Lista uspjesno spremljena u Osobe.txt\n");
    return EXIT_SUCCESS;
}

int loadListFromFile(Person* head) {
    freeMemory(head);

    FILE* file = NULL;

    file = fopen("Osobe.txt", "r");

    if (file == NULL) {
        printf("Greska: Nije moguce pronaci datoteku Osobe.txt\n");
        return SCANF_ERROR;
    }

    Person* prev = head;
    Person* newNode = NULL;

    char tempName[MAX_SIZE];
    char tempSurname[MAX_SIZE];
    int tempYear = 0;

    while (fscanf(file, "%s %s %d", tempName, tempSurname, &tempYear) == 3) {

        newNode = (Person*)malloc(sizeof(Person));
        if (newNode == NULL) {
            printf("Greska alokacije kod ucitavanja.\n");
            fclose(file);
            return MALLOC_ERROR;
        }
        strcpy(newNode->name, tempName);
        strcpy(newNode->surname, tempSurname);
        newNode->birthYear = tempYear;
        newNode->next = NULL;

        prev->next = newNode;

        prev = newNode;
    }
    fclose(file);
    printf("Lista uspjesno ucitana iz Osobe.txt\n");
    return EXIT_SUCCESS;
}