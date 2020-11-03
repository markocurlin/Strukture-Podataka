#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 100

struct node;
typedef struct node* Position;

typedef struct stud {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;   //unsigned 
}Student;

typedef struct node {
	Student student;
	Position next;
}Node;

Student createStudent(void);
Position createNode(Student student);
void insertAfter(Position p, Position q);
void printList(Position p);
void insertEnd(Position p, Position q);
Position findElement(Position p, char* lastName);
void insertAfterEl(Position p, Position q, char* lastName);
void insertBeforeEl(Position p, Position q, char* lastName);
void printToFile(Position p, char* lastName);
void readFromFile(Position p, char* lastName);
void sort(Position p);

int main()
{
	Node head;
	Student student;
	Position el = NULL;
	char lastName[MAX_NAME];
	int i;

	head.next = NULL;
	
	for(i=0; i<3; i++) {
		student = createStudent();
		el = (Position)malloc(sizeof(Node));
		el = createNode(student);

		insertAfter(&head, el);
	}

	printList(&head);

	//Insert at the end
	printf("At the end, ");

	student = createStudent();
	el = (Position)malloc(sizeof(Node));
	el = createNode(student);

	insertEnd(&head, el);

	//Find element
	puts("Find element:");
	scanf("%s", lastName);

	printf("Address: %d\n", findElement(&head, lastName));

	//Insert after
	printf("\nInsert after: ");
	scanf("%s", lastName);

	student = createStudent();
	el = (Position)malloc(sizeof(Node));
	el = createNode(student);

	insertAfterEl(&head, el, lastName);


	//Insert before
	printf("\nInsert before: ");
	scanf("%s", lastName);

	student = createStudent();
	el = (Position)malloc(sizeof(Node));
	el = createNode(student);

	insertBeforeEl(&head, el, lastName);

	printList(&head);

	puts("Sorted list:");

	sort(&head);

	printList(&head);

	//Print and read from file
	printf("Insert name of file: ");
	scanf("%s", lastName);

	//strcpy(lastName, ".txt");
	
	printToFile(&head, lastName);
	
	readFromFile(&head, lastName);

	printList(&head);

	return 0;
}

Student createStudent(void) {
	Student student;

	puts("Enter student:");

	printf("Frist name: ");
	scanf("%s", student.firstName);
	
	printf("Last name: ");
	scanf("%s", student.lastName);
	
	printf("Year of brith: ");
	scanf("%d", &student.birthYear);

	return student;
}

Position createNode(Student student) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Node));

	if ( p == NULL ) {
		perror("Error!");
		return NULL;
	}

	strcpy(p->student.firstName, student.firstName);
	strcpy(p->student.lastName, student.lastName);
	p->student.birthYear = student.birthYear;

	return p;
}

void insertAfter(Position p, Position q) {
	q->next = p->next;
	p->next = q;
}

void insertEnd(Position p, Position q) {
	
	while( p->next != NULL )
		p = p->next;

	insertAfter(p, q);
}

void printList(Position p) {
	Position q = NULL;

	q = p->next;

	puts("\n---LIST CONTENT---");

	while( q != NULL ) {
		printf("First name: %s\nLast name: %s\nYear of birth: %d\t\t%d\n\n", q->student.firstName, q->student.lastName, q->student.birthYear, q);
		q = q->next;
	}
}

Position findElement(Position p, char* lastName) {
	Position q = NULL;

	q = p->next;

	while( q != NULL) {
		if (strcmp(lastName, q->student.lastName) == 0)
			return q;
		q = q->next;
	}

	if ( q == NULL ) {
		printf("Element doesn't exist\n");
		return NULL;
	}
}

void insertAfterEl(Position p, Position q, char* lastName) {
	Position d = NULL;

	d = (Position)malloc(sizeof(Node));

	if ( d == NULL ) 
		perror("Error!");

	d = findElement(p, lastName);

	if ( d != NULL )
		insertAfter(d, q);
}

void insertBeforeEl(Position p, Position q, char* lastName) {
	Position d = NULL;

	d = (Position)malloc(sizeof(Node));

	if ( d == NULL )
		perror("Error!");

	d = findElement(p, lastName);

	while(p->next != d)
		p = p->next;

	if ( d != NULL )
		insertAfter(p, q);
}

void printToFile(Position p, char* lastName) {
	FILE *f;
	Position q = NULL;

	q = p->next;
	
	f = fopen(lastName, "w");

	if ( f == NULL )
		perror("Error!");

	while( q != NULL ) {
		fprintf(f, "%s\t%s\t%d\n", q->student.firstName, q->student.lastName, q->student.birthYear);
		q = q->next;
	}

	fclose(f);
}

void readFromFile(Position p, char* lastName) {
	FILE *f;
	Position q = NULL;

	q = p->next;

	f = fopen(lastName, "r");

	if ( f == NULL )
		perror("Error!");

	while( q != NULL ) {
		fscanf(f, "%s %s %d", q->student.firstName, q->student.lastName, &q->student.birthYear);
		q = q->next;
	}

	fclose(f);
}

void sort(Position p) {
	Position temp = NULL, q = NULL, prevq = NULL, end = NULL;

	while(p->next != end ) {
		prevq = p;
		q = p->next;
		while(q->next != end) {
			if ( strcmp(q->student.lastName, q->next->student.lastName) > 0) {
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
}