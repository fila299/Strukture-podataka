#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPONENT 100

#define MAX_PRODUCT_EXPONENT (MAX_EXPONENT * 2)
#define MAX_LINE 1024

/**
 * Funkcija koja čita JEDAN RED (string) i puni polje 'poly'.
 */
void readPoly(int* poly, char* line) {
    char* ptr = line;
    int coef, exp, n;

    // Petlja koja vrti dok god sscanf uspije naći 2 broja (coef i exp)
    while (sscanf(ptr, " %d %d %n", &coef, &exp, &n) == 2) {

        // spremi u 'n' koliko je znakova pročitao
        // npr. za " 5 3", n će biti 5 (razmak, 5, razmak, 3)

        if (exp < 0 || exp >= MAX_EXPONENT) {
            
            printf("UPOZORENJE: Eksponent %d je prevelik.\n", exp);
        }
        else {
            poly[exp] += coef;
        }

        ptr += n;
    }
}

/**
 * Zbraja dva polinoma.
 */
void addPoly(int* sum, int* poly1, int* poly2) {
    // Samo prođemo kroz oba polja u jednoj petlji.
    for (int i = 0; i < MAX_EXPONENT; i++) {
        // Zbrojimo koeficijente koji stoje na istom indeksu (jer imaju isti eksponent i).
        sum[i] = poly1[i] + poly2[i];
    }
}

/**
 * Množi dva polinoma.
 */
void multiplyPoly(int* product, int* poly1, int* poly2) {
    // Mora sve biti nula prije nego počnemo dodavati rezultate.
    for (int i = 0; i < MAX_PRODUCT_EXPONENT; i++) {
        product[i] = 0;
    }

    // Treba nam dupla petlja da pomnožimo svaki-sa-svakim.

    // Petlja za prvi polinom (uzima 'a' i 'i')
    for (int i = 0; i < MAX_EXPONENT; i++) {
        //  ako je koeficijent 0, ne moramo ništa množiti
        if (poly1[i] == 0) continue;

        // Petlja za drugi polinom
        for (int j = 0; j < MAX_EXPONENT; j++) {
            if (poly2[j] == 0) continue; 

            // Izračunaj novi koeficijent (a*b)
            int newCoef = poly1[i] * poly2[j];
            // Izračunaj novi eksponent (i+j)
            int newExp = i + j;
            product[newExp] += newCoef;
        }
    }
}

void printPoly(int* poly, int size) {
    // 'firstTerm' je zastavica (flag) da znamo jel ovo prvi član
    // koji ispisujemo (da ne stavimo '+' ispred njega).
    int firstTerm = 1;

    // idemo od najvećeg eksponenta prema 0.
    for (int i = size - 1; i >= 0; i--) {

        // Ako je koeficijent 0, samo ga preskoči.
        if (poly[i] != 0) {
            int coef = poly[i];
            int absCoef = (coef > 0) ? coef : -coef; // apsolutna vrijednost

            //  ZNAK (+ / -)
            if (!firstTerm) { // Ako NIJE prvi član...
                // Stavi + ili - ovisno o predznaku
                printf(coef > 0 ? " + " : " - ");
            }
            else if (coef < 0) { // Ako JE prvi član i negativan je...
                printf("-"); // Stavi samo minus
            }

            // 2. KOEFICIJENT
            // Ako je koeficijent 1 (ili -1)
            // ali ako je to slobodni član (x^0), onda moramo napisati npr. "1".
            if (absCoef != 1 || i == 0) {
                printf("%d", absCoef);
            }

            //3. EKSPONENT ('x')
            if (i > 0) { // ako je eksponent veći od 0
                printf("x"); // Uvijek ispiši 'x'
                if (i > 1) { // ako je veći od 1...
                    printf("^%d", i); // ispiši i npr. "^3"
                }
                // Ako je i == 1, ne radi ništa ostat ce samo x
            }

            // Ispisali smo prvi član, spusti zastavicu.
            firstTerm = 0;
        }
    }

    // Ako je cijeli polinom nula, firstTerm će ostat 1.
    // U tom slučaju ispiši "0".
    if (firstTerm) {
        printf("0");
    }

    printf("\n");
}


int main() {
    //polja za polinome i stavlja ih sve na 0
    int poly1[MAX_EXPONENT] = { 0 };
    int poly2[MAX_EXPONENT] = { 0 };
    int sum[MAX_EXPONENT] = { 0 };
    int product[MAX_PRODUCT_EXPONENT] = { 0 };

    char buffer[MAX_LINE];
    FILE* filePointer = fopen("polinomi.txt", "r");

    if (filePointer == NULL) {
        printf("Greska: Ne mogu otvorit 'polinomi.txt'.\n");
        return -1; 
    }

    
    //citanje prvog reda datoteke
    if (fgets(buffer, MAX_LINE, filePointer) == NULL) {
        printf("Greska: Datoteka prazna ili ne mogu citat prvi red.\n");
        fclose(filePointer);
        return -1;
    }
    // salje taj red u funkciju da popuni poly1
    readPoly(poly1, buffer);

    //citanje drugog reda datoteke
    if (fgets(buffer, MAX_LINE, filePointer) == NULL) {
        printf("Greska: Ne mogu citat drugi red.\n");
        fclose(filePointer);
        return -1;
    }
    // salje taj red u funkciju da popuni poly2
    readPoly(poly2, buffer);

    fclose(filePointer);

    // Ispis i pozivanje funkcija
    printf("Polinom 1: ");
    printPoly(poly1, MAX_EXPONENT);

    printf("Polinom 2: ");
    printPoly(poly2, MAX_EXPONENT);

    addPoly(sum, poly1, poly2);
    printf("\nSuma:      ");
    printPoly(sum, MAX_EXPONENT);

    multiplyPoly(product, poly1, poly2);
    printf("Produkt:   ");
    printPoly(product, MAX_PRODUCT_EXPONENT);

    return 0;
}