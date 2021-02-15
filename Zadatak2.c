#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 256

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

Position CreateNode(Person per);
int insertAfter(Position p, Position q);
int insertAtEnd(Position p, Position q);
int deleteNode(Position p, Position q);
Position find(Position p, char* lastName);
int print(Position p);

int main()
{
	Node head;
	Position p = NULL;
	Person per;
	char lastName[NAME_SIZE];
	int i = 0;

	head.next = NULL;

	for(i = 0; i < 3; i++) {
		printf("Insert first name of person: ");
		scanf("%s", per.firstName);
		printf("Insert last name of person: ");
		scanf("%s", per.lastName);
		printf("Insert year of birth: ");
		scanf("%d", &per.yearOfBirth);

		p = (Position)malloc(sizeof(Node));
		p = CreateNode(per);
		insertAfter(&head, p);
	}

	print(head.next);

	puts(" ");

	printf("Insert first name of person: ");
	scanf("%s", per.firstName);
	printf("Insert last name of person: ");
	scanf("%s", per.lastName);
	printf("Insert year of birth: ");
	scanf("%d", &per.yearOfBirth);
	p = CreateNode(per);

	insertAtEnd(&head, p);

	print(head.next);

	printf("Insert last name of person: ");
	scanf("%s", lastName);

	p = find(&head, lastName);
	printf("%s\t%s\t%d\n", p->per.firstName, p->per.lastName, p->per.yearOfBirth);

	printf("Insert last name of person: ");
	scanf("%s", lastName);

	p = find(&head, lastName);
	deleteNode(&head, p);

	print(head.next);

	return 0;
}

int insertAfter(Position p, Position q) {
	q->next = p->next;
	p->next = q;

	return 0;
}

int insertAtEnd(Position p, Position q) {
	while(p->next != NULL)
		p = p->next;

	insertAfter(p, q);

	return 0;
}

Position find(Position p, char* lastName) {
	Position q = NULL;
	q = p->next;

	while( q->next != NULL && strcmp(q->per.lastName, lastName) != 0 )
		q = q->next;

	if ( q->next == NULL) {
		puts("Element doesn't exist!");
		return NULL;
	}

	return q;
}

Position CreateNode(Person per) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	if ( q == NULL )
		perror("Error!\n");

	q->per = per;

	return q;
}

int deleteNode(Position p, Position q) {
	if ( q == NULL ) {
		puts("Error!");
		return 0;
	}

	while( p->next != q )
		p = p->next;

	p->next = q->next;
	free(q);

	return 0;
}

int print(Position p) {

	while( p != NULL ) {
		printf("%s\t%s\t%d\n", p->per.firstName, p->per.lastName, p->per.yearOfBirth);
		p = p->next;
	}

	return 0;
}