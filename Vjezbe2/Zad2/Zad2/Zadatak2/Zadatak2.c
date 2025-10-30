/*
Zadatak:
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   // za tolower()

// Konstante
#define MAX_SIZE 50
#define EXIT_SUCCESS 1
#define SCANF_ERROR -1
#define MALLOC_ERROR -2

// Deklaracija strukture i tipova pokazivača
struct _person;
typedef struct _person* Position;

// Deklaracija funkcija
Position createPerson();
int addToFrontOfTheList(Position);
int addToEndOfTheList(Position);
int printList(Position);
int printPerson(Position);
Position findPerson(Position, char*);
int deletePerson(Position, char*);

// Definicija strukture "Person"
typedef struct _person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;   // pokazivač na sljedeći element u listi
} Person;

int main() {

    char input = 0;
    char surname[MAX_SIZE];

    // head koji služi kao početak liste (ne sadrži pravu osobu)
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    printf("a - add person to front of the list\n");
    printf("b - print list\n");
    printf("c - add person to end of the list\n");
    printf("d - find person with surname\n");
    printf("e - delete person with surname\n");
    printf("0 - exit program\n");

    do {
        printf("\nChoose action: ");
        if (scanf(" %c", &input) != 1) return SCANF_ERROR;
        input = tolower(input); // pretvara unos u malo slovo

        switch (input) {
        case 'a':
            printf("Add to front of the list\n");
            addToFrontOfTheList(&head);
            break;

        case 'b':
            printf("Printing list:\n");
            printList(head.next);
            break;

        case 'c':
            printf("Add to end of the list\n");
            addToEndOfTheList(&head);
            break;

        case 'd':
            printf("Find person with surname: ");
            if (scanf(" %s", surname) != 1) return SCANF_ERROR;

            // tražimo osobu po prezimenu
            Position found = findPerson(head.next, surname);
            if (found) {
                printPerson(found);
            }
            else {
                printf("\tPerson with surname %s was not found.\n", surname);
            }
            break;

        case 'e':
            printf("Delete person with surname: ");
            if (scanf(" %s", surname) != 1) return SCANF_ERROR;
            deletePerson(&head, surname);
            break;

        case '0':
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid input. Try again.\n");
            break;
        }
    } while (input != '0');  // izlazak iz programa

    return EXIT_SUCCESS;
}
    // Funkcija koja stvara novi čvor (osobu) dinamički pomoću malloc()
Position createPerson() {
    Position person = NULL;
    person = (Position)malloc(sizeof(Person));  // alokacija memorije

    if (!person) { // provjera da malloc nije vratio NULL
        printf("Malloc error.\n");
        return NULL;
    }

    // unos podataka za osobu
    printf("\tName: ");
    if (scanf(" %s", person->name) != 1) return NULL;

    printf("\tSurname: ");
    if (scanf(" %s", person->surname) != 1) return NULL;

    printf("\tBirth year: ");
    if (scanf(" %d", &person->birthYear) != 1) return NULL;

    person->next = NULL; // na početku nema sljedećeg elementa
    return person;
}
  //Funkcija koja ispisuje podatke jedne osobe

int printPerson(Position person) {
    if (person != NULL) {
        printf("Name: %s\n", person->name);
        printf("Surname: %s\n", person->surname);
        printf("Birth Year: %d\n", person->birthYear);
    }
    return EXIT_SUCCESS;
}
    //Funkcija koja ispisuje cijelu listu osoba
int printList(Position person) {
    if (person == NULL) {
        printf("Empty list.\n");
        return EXIT_SUCCESS;
    }

    while (person != NULL) {
        printPerson(person);
        printf("----------------------\n");
        person = person->next; // pomak na sljedeću osobu
    }
    return EXIT_SUCCESS;
}
    //Dodaje novu osobu na početak liste, odmah iza head čvora
int addToFrontOfTheList(Position head) {
    Position newPerson = createPerson(); // napravi novu osobu

    if (!newPerson) {
        printf("Malloc error.\n");
        return MALLOC_ERROR;
    }

    // povezivanje novog elementa
    newPerson->next = head->next; // nova osoba pokazuje na ono što je prije bilo prvo
    head->next = newPerson;       // head sada pokazuje na novu osobu

    return EXIT_SUCCESS;
}
    //Dodaje novu osobu na kraj liste

int addToEndOfTheList(Position head) {
    Position newPerson = createPerson();

    if (!newPerson) {
        printf("Malloc error.\n");
        return MALLOC_ERROR;
    }

    // prolazimo kroz listu dok ne nađemo zadnji element
    while (head->next != NULL) {
        head = head->next;
    }

    // kad smo došli do kraja, novi element postaje zadnji
    newPerson->next = head->next; // što znači NULL
    head->next = newPerson;

    return EXIT_SUCCESS;
}
    //Traži osobu po prezimenu i vraća pokazivač na nju
Position findPerson(Position current, char* sur) {
    while (current != NULL) {
        if (strcmp(current->surname, sur) == 0) { // usporedba prezimena
            return current; // ako se podudara, vrati tu osobu
        }
        current = current->next; // idi dalje po listi
    }
    return NULL; // ako nije pronađena
}
    //Briše osobu iz liste po prezimenu
int deletePerson(Position head, char* sur) {
    Position temp = NULL;
    Position prev = head; // prev pokazuje na element ispred onog koji brišemo

    // tražimo osobu čije prezime odgovara
    while (prev->next != NULL && strcmp(prev->next->surname, sur) != 0) {
        prev = prev->next;
    }

    // ako nije pronađena
    if (prev->next == NULL) {
        printf("Person with surname %s was not found.\n", sur);
        return EXIT_SUCCESS;
    }

    // brisanje osobe iz liste
    temp = prev->next;         // pokazuje na osobu koju brišemo
    prev->next = temp->next;   // preskačemo je 
    free(temp);                // oslobađamo memoriju

    printf("Person deleted.\n");
    return EXIT_SUCCESS;
}
