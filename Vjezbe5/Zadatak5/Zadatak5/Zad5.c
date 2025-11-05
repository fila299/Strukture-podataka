#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024
#define ALLOCATION_ERROR -1
#define FILE_NOT_FOUND_ERROR -2
#define ERROR -3

struct _member;
typedef struct _member* position;
typedef struct _member {
	float number;
	position next;
}member;

float fileinput(char filename[MAX_LINE]);
int printPostfix(char filename[MAX_LINE]);
int pop(float* temp);
int push(float* temp);
int Delete();

position top = NULL;

int main() {
	float result;

	char filename[MAX_LINE] = "Stack.txt";

	printf("Citam postfiks izraz iz datoteke: %s\n", filename);

	printPostfix(filename);

	result = fileinput(filename);
	if (result != ERROR) {
		printf("\nRezultat je %.2f.", result);
	}
	else {
		printf("Netocno postavljena jednadzba u datoteci!");
	}

	Delete();
	return 0;
}

float fileinput(char filename[MAX_LINE]) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Datoteka '%s' nije pronadjena!\n", filename);
		return FILE_NOT_FOUND_ERROR;
	}
	int n = 0;
	int l;
	float temp1 = 0;
	float temp2 = 0;
	float* tmp1 = &temp1;
	float* tmp2 = &temp2;
	char ctemp[MAX_LINE];
	char oper[MAX_LINE];
	float res;
	float* tempres;
	tempres = &res;

	fgets(ctemp, MAX_LINE, fp);
	fclose(fp);

	char* p = ctemp;

	while (strlen(p) > 0 && p[0] != '\n') {
		l = sscanf(p, "%f %n", &temp1, &n);

		if (l == 1) {
			push(tmp1);
		}
		else {
			l = sscanf(p, "%s %n", oper, &n);
			if (l != 1) break;

			if (!strcmp(oper, "+")) {
				pop(tmp1);
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 + temp1;
				push(tempres);
			}
			else if (!strcmp(oper, "-")) {
				pop(tmp1);
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 - temp1;
				push(tempres);
			}
			else if (!strcmp(oper, "*")) {
				pop(tmp1);
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 * temp1;
				push(tempres);
			}
			else if (!strcmp(oper, "/")) {
				pop(tmp1);
				if (temp1 == 0) {
					printf("Dijeljenje s 0 nije moguce!\n");
					return ERROR;
				}
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 / temp1;
				push(tempres);
			}
			else {
				if (n == 0) n = 1;
			}

		}
		p += n;
	}

	pop(tmp1);

	if (top != NULL) {
		printf("Greska: Vise elemenata na stogu, krivi izraz.\n");
		return ERROR;
	}

	return *tmp1;
}

int printPostfix(char filename[MAX_LINE])
{
	printf("\nPostfiks iz datoteke: ");

	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Datoteka '%s' jos ne postoji.\n", filename);
		return FILE_NOT_FOUND_ERROR;
	}

	char line[MAX_LINE];

	while (fgets(line, MAX_LINE, fp) != NULL)
	{
		printf("%s", line);
	}

	fclose(fp);
	printf("\n");
	return 0;
}

int push(float* temp) {
	position q;
	q = (position)malloc(sizeof(member));
	if (q == NULL) {
		printf("Ne mogu alocirati memoriju!\n");
		return ALLOCATION_ERROR;
	}
	q->number = *temp;
	q->next = top;
	top = q;
	return 0;
}

int pop(float* temp) {
	position q;
	if (top == NULL) {
		printf("Stog je prazan!\n");
		*temp = ERROR;
		return ERROR;
	}

	*temp = top->number;

	q = top;
	top = top->next;
	free(q);
	return 0;
}

int Delete() {
	position head = top;
	position temp;

	while (head != NULL) {
		temp = head->next;
		free(head);
		head = temp;
	}
	top = NULL;
	return 0;
}