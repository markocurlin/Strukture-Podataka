#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 11
#define HASH_FUNCTION 5
#define NAME_SIZE 256

typedef struct student {
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int mb;
} Student;

struct node;
typedef struct node* Position;
typedef struct node {
	Student s;
	Position next;
} Node;


Student createStudent();
Position createNode(Student s);
int insertAfter(Position p, Student s);
int hashFunction(char* lastName);
int insertInTable(Position p, Student s);
int search(Position p, char* firstName, char* lastName);
int printTable(Position p);

int main()
{
	Node hash[HASH_SIZE];
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	Student s;
	int i;

	for(i = 0; i < HASH_SIZE; i++)
		hash[i].next = NULL;

	for(i = 0; i < HASH_SIZE; i++) {
		s = createStudent();
		insertInTable(hash, s); 
	}

	printTable(hash);

	printf("Insert first name: ");
	scanf("%s", firstName);
	printf("Insert last name: ");
	scanf("%s", lastName);

	search(hash, firstName, lastName);

	return 0;
}

Student createStudent() {
	Student s;

	printf("Insert first name: ");
	scanf("%s", s.firstName);
	printf("Insert last name: ");
	scanf("%s", s.lastName);
	printf("Insert MB: ");
	scanf("%d", &s.mb);

	return s;
}

Position createNode(Student s) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	if (q == NULL) {
		perror("Error allocating memory!\n");
		return NULL;
	}

	q->s = s;
	q->next = NULL;

	return q;
}

int insertAfter(Position p, Student s) {
	Position q = NULL;

	q = createNode(s);

	if (q != NULL) {
		while(p->next != NULL && (strcmp(p->next->s.lastName, s.lastName) < 0 || (strcmp(p->next->s.lastName, s.lastName) == 0 && strcmp(p->next->s.firstName, s.firstName) < 0)))
			p = p->next;
		q->next = p->next;
		p->next = q;
	}

	return 0;
}

int hashFunction(char* lastName) {
	int rez = 0, i;

	for(i = 0; i < HASH_FUNCTION; i++) {
		if (lastName[i] == '\0')
			break;
		rez += lastName[i];
	}

	return rez % HASH_SIZE;
}

int insertInTable(Position p, Student s) {
	int key = 0;

	if (p == NULL) {
		printf("Empry table!\n");
		return 0;
	}

	key = hashFunction(s.lastName);

	insertAfter((p + key), s);
	
	return 0;
}

int search(Position p, char* firstName, char* lastName) {
	Position q = NULL;
	int key = 0;

	if (p == NULL) {
		printf("Empry table!\n");
		return 0;
	}

	key = hashFunction(lastName);

	if ((p + key) != NULL) {
		q =  (p + key);
	}
	
	else {
		printf("Element doesn't exist!\n");
		return 0;
	}

	while(q != NULL && strcmp(q->s.firstName, firstName) != 0)
		q = q->next;

	if (q == NULL) {
		printf("Element doesn't exist!\n");
		return 0;
	}

	else {
		printf("MB: %d\n", q->s.mb);
		return 0;
	}

	return 0;
}

int printTable(Position p) {
	Position q = NULL;
	int i;

	if (p == NULL) {
		printf("Empry table!\n");
		return 0;
	}

	for(i = 0; i < HASH_SIZE; i++) {
		printf("KEY: %d\n", i);
		if ((p + i)->next != NULL) {
			puts("FIRST NAME\tLAST NAME\tMB");
			for(q = (p + i)->next; q != NULL; q = q->next)
				printf("%s\t%s\t%d\n", q->s.firstName, q->s.lastName, q->s.mb);
		}
	}

	return 0;
}