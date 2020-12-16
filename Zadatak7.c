#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 100

struct node;
typedef struct node* Stog;
typedef struct node {
	int el;
	Stog next;
}Node;

char* readFromFile(char* nameOfFile);
int push(Stog p, int el);
int pop(Stog p);
int calculateInfix(Stog p, char* buffer);
int operation(int a, int b, char c);
int printList(Stog p);

int main()
{
	Node head;
	char* buffer = NULL;
	char nameOfFile[M];

	head.next = NULL;

	printf("Insert name of file: ");
	scanf("%s", nameOfFile);
	strcat(nameOfFile, ".txt");

	buffer = readFromFile(nameOfFile);

	printf("%s\n", buffer);

	calculateInfix(&head, buffer);
	printList(&head);

	return 0;

}

char* readFromFile(char* nameOfFile) {
	FILE* f = NULL;
	char* buffer = NULL;

	f = fopen(nameOfFile, "r");

	if (!f)
		perror("Error!\n");

	buffer = (char*)malloc(1000*sizeof(char));

	if (!buffer)
		perror("Error!\n");

	fgets(buffer, 1000*sizeof(buffer), f);

	fclose(f);

	return buffer;
}

int push(Stog p, int el) {
	Stog q = NULL;

	q = (Stog)malloc(sizeof(Node));
	
	if (!q)
		perror("Error!");
	q->el = el;
	
	q->next = p->next;
	p->next = q;

	return 0;
}

int pop(Stog p) {
	Stog q = NULL;
	int el;

	if (p->next != NULL) {
		q = p->next;
		el = q->el;
		p->next = q->next;
		free(q);
	}

	return el;
}

int calculateInfix(Stog p, char* buffer) {
	int el = 0, result = 0, m = 0;
	char c;

	while(*buffer != '\0') {
		if ( sscanf(buffer, "%d %n", &el, &m) ) {
			buffer+=m;
			push(p, el);
		}

		else if ( sscanf(buffer, "%c %n", &c, &m) ) {
			buffer+=m;
			result = operation(pop(p), pop(p), c);
			push(p, result);
		}
	}

	return 0;
}

int operation(int a, int b, char c) {

	switch(c) {
		case '+':
			return (a + b);
			break;
		case '-':
			return (a - b);
			break;
		case '*':
			return (a * b);
			break;
		case '/':
			return (a/b);
			break;
		default:
			puts("Error!");
			return 0;
			break;			
	}
}

int printList(Stog p) {
	p = p->next;

	puts("-----LIST CONTENT-----");

	while(p !=NULL ) {
		printf("%d " , p->el);
		p = p->next;
	}

	puts(" ");

	return 0;
}