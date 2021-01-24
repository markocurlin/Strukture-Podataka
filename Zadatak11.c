#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_SIZE 1024
#define HASH_SIZE 11
#define HASH_FUNCTION 5

struct node;
typedef struct node* Position;
typedef struct node {
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int mb;
	Position next;
} Node;

int createNode(Position p, char* firstName, char* lastName, int mb);
int hashFunction(char* lastName);
int addToTable(Position p, char* firstName, char* lastName, int mb);
int printTable(Position p);
int search(Position p, char* firstName, char* lastName);

int main()
{
	Node hash[HASH_SIZE];
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];
	int mb, i;

	for( i = 0; i < HASH_SIZE; i++ )
		hash[i].next = NULL;

	for( i = 0; i < 8; i++ ) {
		printf("Insert first name: ");
		scanf(" %s", firstName);
		printf("Insert last name: ");
		scanf(" %s", lastName);
		printf("Insert MB: ");
		scanf(" %d", &mb);

		addToTable(hash, firstName, lastName, mb);
	}

	printTable(hash);

	puts("FIND PERSON");
	printf("Insert first name: ");
	scanf(" %s", firstName);
	printf("Insert last name: ");
	scanf(" %s", lastName);

	search(hash, firstName, lastName);
	
	return 0;
}

int createNode(Position p, char* firstName, char* lastName, int mb) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	if ( q == NULL ) {
		perror("Error!");
		return 0;
	}

	strcpy(q->firstName, firstName);
	strcpy(q->lastName, lastName);
	q->mb = mb;

	while(p->next != NULL && ( strcmp(p->next->lastName, lastName) < 0  || (strcmp(p->next->lastName, lastName) == 0 && strcmp(p->next->firstName, firstName) < 0 )))
		p = p->next;

	q->next = p->next;
	p->next = q;

	return 0;
}

int hashFunction(char* lastName) {
	int i, size = 0;

	for(i = 0; i < HASH_FUNCTION; i++) {
		if (lastName[i] == '\0')
			break;
		size += lastName[i];
	}

	return size % HASH_SIZE;
}

int addToTable(Position p, char* firstName, char* lastName, int mb) {
	int key;

	if (p == NULL) {
		puts("Empty table!");
		return 0;
	}

	key = hashFunction(lastName);

	createNode((p+key), firstName, lastName, mb);

	return 0;
}

int search(Position p, char* firstName, char* lastName) {
	Position q = NULL;
	int key;

	if (p == NULL) {
		puts("Empty table!");
		return 0;
	}

	key = hashFunction(lastName); 

	if ( (p+key) != NULL )
		q = (p+key);
	
	else {
		puts("Element doesn't exist!");
		return 0;
	}
	
	while( q != NULL && strcmp(q->firstName, firstName) != 0 )
		q = q->next;
	
	if ( q == NULL ) {
		puts("Element doesn't exist!");
		return 0;
	}

	else {
		printf("MB: %d\n", q->mb);
		return 0;
	}
}

int printTable(Position p) {
	int i;
	Position q = NULL;

	for( i = 0; i < HASH_SIZE; i++ ) {
		printf("KEY: %d\n", i);
		if ((p+i)->next != NULL) {
			puts("FIRST NAME\tLAST NAME\tMB");
			for(q = (p+i)->next; q != NULL; q = q->next)
				printf("%s\t\t%s\t\t%d\n", q->firstName, q->lastName, q->mb);
		}
	}

	return 0;
}