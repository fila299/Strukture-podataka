#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 50
#define EXIT_SUCCESS 1
#define SCANF_ERROR -1
#define MALLOC_ERROR -2

struct _person;
typedef struct _person* Position;

typedef struct _person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
} Person;

Position createPerson();
int addToFrontOfTheList(Position);
int printList(Position);
int printPerson(Position);

int main() {
    char input = 0;
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    printf("a - add person to front of the list\nb - print list\n0 - exit\n");

    do {
        printf("\nChoose action: ");
        if (scanf(" %c", &input) != 1) return SCANF_ERROR;
        input = tolower(input);

        switch (input) {
        case 'a':
            printf("Add to front of the list\n");
            addToFrontOfTheList(&head);
            break;

        case 'b':
            printf("Printing list:\n");
            printList(head.next);
            break;

        case '0':
            break;

        default:
            printf("Invalid input. Try again.\n");
            break;
        }
    } while (input != '0');

    return EXIT_SUCCESS;
}

Position createPerson() {
    Position person = NULL;
    person = (Position)malloc(sizeof(Person));

    if (!person) {
        printf("Malloc error.\n");
        return NULL;
    }

    printf("\tName: ");
    if (scanf(" %s", person->name) != 1) return NULL;

    printf("\tSurname: ");
    if (scanf(" %s", person->surname) != 1) return NULL;

    printf("\tBirth year: ");
    if (scanf(" %d", &person->birthYear) != 1) return NULL;

    person->next = NULL;
    return person;
}

int printPerson(Position person) {
    if (person != NULL) {
        printf("Name: %s\n", person->name);
        printf("Surname: %s\n", person->surname);
        printf("Birth Year: %d\n\n", person->birthYear);
    }
    return EXIT_SUCCESS;
}

int printList(Position person) {
    if (person == NULL) {
        printf("Empty list.\n");
        return EXIT_SUCCESS;
    }

    while (person != NULL) {
        printPerson(person);
        person = person->next;
    }
    return EXIT_SUCCESS;
}

int addToFrontOfTheList(Position head) {
    Position newPerson = createPerson();
    if (!newPerson) {
        printf("Error creating new person.\n");
        return MALLOC_ERROR;
    }

    newPerson->next = head->next;
    head->next = newPerson;

    return EXIT_SUCCESS;
}
