#define _CRT_SECURE_NO_WARNINGS
#define MAX_BODOVA 100.0

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[50];
    char prezime[50];
    int bodovi;
} Student;

int ucitajDatoteku(const char* filename, Student** studenti) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;

    Student* niz = NULL;
    int brojac = 0;

    while (1) {
        Student temp;
        if (fscanf(file, "%s %s %d", temp.ime, temp.prezime, &temp.bodovi) != 3)
            break;

        Student* novaLista = realloc(niz, (brojac + 1) * sizeof(Student));
        if (!novaLista) {
            free(niz);
            fclose(file);
            return 1;
        }

        niz = novaLista;
        niz[brojac] = temp;
        brojac++;
    }

    fclose(file);
    *studenti = niz;
    return brojac;
}

int ispisDatoteke(Student* studenti, int brojStudenata) {
    if (!studenti) return -1;

    printf("Ime\tPrezime\tBodovi\tPostotak\n");
    printf("----------------------------\n");

    for (int i = 0; i < brojStudenata; i++) {
        double postotak = (studenti[i].bodovi / MAX_BODOVA) * 100.0;
        printf("%s\t%s\t%d\t%.2f\n",
            studenti[i].ime,
            studenti[i].prezime,
            studenti[i].bodovi,
            postotak);
    }

    return 0;
}

int main() {
    Student* studenti = NULL;

    int brojStudenata = ucitajDatoteku("Studenti.txt", &studenti);
    if (brojStudenata == -1) {
        printf("Greska pri citanju datoteke ili alokaciji memorije.\n");
        return 1;
    }

    if (ispisDatoteke(studenti, brojStudenata) == -1) {
        printf("Greska pri ispisu podataka.\n");
        free(studenti);
        return 1;
    }

    free(studenti);
}