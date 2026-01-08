#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct Directory {
    char name[MAX_NAME];
    struct Directory* child;
    struct Directory* sibling;
    struct Directory* parent;
} Directory;

Directory* createDir(char* name, Directory* parent) {
    Directory* dir = (Directory*)malloc(sizeof(Directory));
    strcpy(dir->name, name);
    dir->child = NULL;
    dir->sibling = NULL;
    dir->parent = parent;
    return dir;
}


void makeDir(Directory* current, char* name) {
    Directory* newDir = createDir(name, current);

    if (current->child == NULL) {
        current->child = newDir;
    }
    else {
        Directory* temp = current->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = newDir;
    }
}


void listDir(Directory* current) {
    Directory* temp = current->child;

    if (temp == NULL) {
        printf("Direktorij je prazan.\n");
        return;
    }

    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->sibling;
    }
}


Directory* changeDir(Directory* current, char* name) {
    Directory* temp = current->child;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }

    printf("Direktorij ne postoji.\n");
    return current;
}


Directory* goBack(Directory* current) {
    if (current->parent != NULL)
        return current->parent;

    printf("Vec ste u root direktoriju.\n");
    return current;
}


int main() {
    int choice;
    char name[MAX_NAME];

    Directory* root = createDir("root", NULL);
    Directory* current = root;

    while (1) {
        printf("\nTrenutni direktorij: %s\n", current->name);
        printf("1 - md\n");
        printf("2 - cd dir\n");
        printf("3 - cd..\n");
        printf("4 - dir\n");
        printf("5 - izlaz\n");
        printf("Odabir: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Ime direktorija: ");
            scanf("%s", name);
            makeDir(current, name);
            break;

        case 2:
            printf("Ime direktorija: ");
            scanf("%s", name);
            current = changeDir(current, name);
            break;

        case 3:
            current = goBack(current);
            break;

        case 4:
            listDir(current);
            break;

        case 5:
            printf("Izlaz iz programa.\n");
            return 0;

        default:
            printf("Pogresan odabir.\n");
        }
    }
}
