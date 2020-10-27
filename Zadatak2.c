#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 100

struct node;

typedef struct node* Position;

typedef struct node{
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;
}Node;

Position getLast(Position p) {
	Position q = p->next;

	while( NULL != q->next )
		q=q->next;

	return q;
}

Position findElement(Position p, char* lastName) {
	Position q = p->next;

	while(q!=NULL) {
		if ( strcmp(q->lastName, lastName) == 0 )
			return q;
		q=q->next;
	}

	return NULL;
}

Position createList(char* firstName, char* lastName, int birthYear) {
	Position el;

	el = (Position)malloc(sizeof(Node));

	if ( NULL == el ) 
		perror("Error!");

	strcpy(el->firstName, firstName);
	strcpy(el->lastName, lastName);
	el->birthYear = birthYear;
	el->next = NULL;

	return el;
}

void insertAfter(Position p, Position q) {
	q->next = p->next;
	p->next = q;
}

void deleteElement(Position p, Position q) {

	if (q==NULL)
		printf("Error!");

	while(p->next != q )
		p=p->next;

	p->next=q->next;

	free(q);

}

void printList(Position p) {
	Position q = p->next;

	puts("\n---LIST CONTENT---");

	while ( NULL != q ) {
		printf("%s\t%s\t%d\t\n", q->firstName, q->lastName, q->birthYear);
		q = q->next;
	}

}

int main()
{
	Node head;
	Position el = NULL;

	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	char c;
	int birthYear = 0;

	head.next = NULL;
	
	while(1)
	{
		puts("Please insert person");

		printf("First name:\t");
		scanf("%s", firstName);

		printf("Last name:\t");
		scanf("%s", lastName);

		printf("Year of birth:\t");
		scanf("%d", &birthYear);

		el = (Position)malloc(sizeof(Node));

		el = createList(firstName, lastName, birthYear);

		insertAfter(&head, el);

		puts("Press C to continue...");

		scanf("%c", &c);

		if ( c=getchar() != 'C')
			break;

	}

	printList(&head);
	
	//Insert person to the end of the list
	puts("\nInsert person to the end of the list");
	
	printf("First name:\t");
	scanf("%s", firstName);

	printf("Last name:\t");
	scanf("%s", lastName);

	printf("Year of birth:\t");
	scanf("%d", &birthYear);

	el = (Position)malloc(sizeof(Node));
	el = createList(firstName, lastName, birthYear);
	 
	insertAfter(getLast(&head), el);

	printList(&head);

	puts(" ");

	//Find element
	printf("Find element\nLast name:\t");
	scanf("%s", lastName);

	printf("Address of element:\t%d\n\n", findElement(&head, lastName));

	//Delete element

	printf("Delete element\nLast name:\t");
	scanf("%s", lastName);

	deleteElement(&head, findElement(&head, lastName));

	printList(&head);

	return 0;
}