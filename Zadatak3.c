#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 256
#define FILE_SIZE 256

typedef struct person {
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int yearOfBirth;
} Person;

struct node;
typedef struct node* Position;
typedef struct node {
	Person per;
	Position next;
} Node;

Position createNode(Person per);
Person createPerson();
int insertAfter(Position p, Position q);
int insertAtEnd(Position p, Position q);
int deleteNode(Position p, char* lastName);
int deleteAll(Position p);
int insertAfterNode(Position p, Position q, char* lastName);
int insertBeforeNode(Position p, Position q, char* lastName);
int print(Position p);
int printToFile(Position p, char* fileName);
int readFromFile(Position p, char* fileName);
int sortUnos(Position p, Position q);
Position find(Position p, char* lastName);
Position findB(Position p, char* lastName);
int sort(Position p);

int main()
{
	Node head;
	Person per;
	Position pos;
	char lastName[NAME_SIZE];
	int i = 0;

	head.next = NULL;

	/*for(i = 0; i < 3; i++) {
		per = createPerson();
		pos = (Position)malloc(sizeof(Node));
		pos = createNode(per);
		sortUnos(&head, pos);
	}

	print(head.next);

	printf("Insert last name: ");
	scanf("%s", lastName); 
	per = createPerson();
	pos = (Position)malloc(sizeof(Node));
	pos = createNode(per);
	insertAfterNode(&head, pos, lastName);

	printf("Insert last name: ");
	scanf("%s", lastName); 
	per = createPerson();
	pos = (Position)malloc(sizeof(Node));
	pos = createNode(per);
	insertBeforeNode(&head, pos, lastName);

	print(head.next);

	//deleteAll(&head);

	//print(head.next);*/
	
	sort(&head);
	
	printf("Insert name of file: ");
	scanf("%s", lastName);
	
	//printToFile(head.next, lastName);
	
	readFromFile(&head, lastName);
	print(head.next);

	return 0;
}

Position createNode(Person per) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	if (q == NULL) {
		perror("Error!\n");
		return NULL;
	}

	q->per = per;

	return q;
}

Position findB(Position p, char* lastName) {
	while(p->next != NULL && strcmp(p->next->per.lastName, lastName) != 0)
		p = p->next;

	if ( p->next == NULL)
		return NULL;

	return p;
}

Position find(Position p, char* lastName) {
	while(p != NULL && strcmp(p->per.lastName, lastName) != 0)
		p = p->next;

	if ( p == NULL)
		return NULL;

	return p;
}

int sortUnos(Position p, Position q) {
	while(p->next != NULL && strcmp(p->next->per.lastName, q->per.lastName) < 0 )
		p = p->next;
	
	insertAfter(p, q);

	return 0;
}

int insertAfterNode(Position p, Position q, char* lastName) {
	p = find(p, lastName);
	if ( p != NULL )
		insertAfter(p, q);

	return 0;
}

int insertBeforeNode(Position p, Position q, char* lastName) {
	p = findB(p, lastName);
	if ( p != NULL )
		insertAfter(p, q);

	return 0;
}

int insertAfter(Position p, Position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int print(Position p) {
	if (p == NULL)
		puts("Empty!");

	while(p != NULL) {
		printf("%s\t%s\t%d\n", p->per.firstName, p->per.lastName, p->per.yearOfBirth);
		p = p->next;
	}

	return 0;
}

int printToFile(Position p, char* fileName) {
	FILE* f;

	f = fopen(fileName, "w");

	if ( f == NULL ) {
		perror("Error!\n");
		return 0;
	}

	while(p->next != NULL) {
		fprintf(f, "%s\t%s\t%d\n", p->per.firstName, p->per.lastName, p->per.yearOfBirth);
		p = p->next;
	}
	
	fclose(f);

	return 0;
}

int readFromFile(Position p, char* fileName) {
	FILE* f;
	Position q = NULL;
	Person per;
	int br = 0, i;

	f = fopen(fileName, "r");

	if ( f == NULL ) {
		perror("Error!\n");
		return 0;
	}

	while(!feof(f)) {
		if (getc(f) == '\n')
			br++;
	}

	rewind(f);

	q = (Position)malloc(sizeof(Node));

	for(i = 0; i < br; i++) {
		fscanf(f, "%s %s %d", per.firstName, per.lastName, &per.yearOfBirth);
		q = createNode(per);
		insertAtEnd(p, q);
	}

	fclose(f);

	return 0;
}

int insertAtEnd(Position p, Position q) {
	while(p->next != NULL)
		p = p->next;
	insertAfter(p, q);

	return 0;
}

int deleteNode(Position p, char* lastName) {
	Position q = NULL;

	q = find(p, lastName);

	p->next = q->next;
	free(q);

	return 0;
}

int deleteAll(Position p) {
	Position Poc = p;
	Position prev = p;

	p = p->next;

	while(Poc->next != NULL) {
		while(p->next != NULL) {
			prev = p;
			p = p->next;
		}

		free(p);
		prev->next = NULL;

		p = Poc->next;
		prev = Poc;
	}

	return 0;

	/*
	ILI
	Position temp = NULL;

	while(p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	*/
}

Person createPerson() {
	Person per;
	printf("Insert first name of person: ");
	scanf("%s", per.firstName);
	printf("Insert last name of person: ");
	scanf("%s", per.lastName);
	printf("Insert year of birth: ");
	scanf("%d", &per.yearOfBirth);

	return per;
}


int sort(Position p) {
	Position temp = NULL, q = NULL, prevq = NULL, end = NULL;

	while(p->next != end ) {
		prevq = p;
		q = p->next;
		while(q->next != end) {
			if ( strcmp(q->per.lastName, q->next->per.lastName) > 0) {
				temp = q->next;
				prevq->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}

			prevq = q;
			q = q->next;
		}
		end = q;
	}
	return 0;
}