#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node;
typedef struct node* Position;
typedef struct node {
	int el;
	Position next;
} Node;

int push(Position p, int el);
int popS(Position p);
int popR(Position p);
int print(Position p);

int main()
{
	Node headS, headR;
	int i, el;

	headS.next = NULL;
	headR.next = NULL;

	srand((unsigned)time(NULL));

	puts("STOG");

	for(i = 0; i < 8; i++) {
		el = rand() % 89 + 10;
		push(&headS, el);
	}

	print(headS.next);

	for(i = 0; i < 8; i++)
		printf("POP: %d\n", popS(&headS));

	print(headS.next);

	puts("RED");

	for(i = 0; i < 11; i++) {
		el = rand() % 89 + 10;
		push(&headR, el);
	}

	print(headR.next);

	for(i = 0; i < 11; i++)
		printf("POP: %d\n", popR(&headR));

	print(headR.next);

	return 0;
}

int push(Position p, int el) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));
	
	if (q == NULL) {
		perror("Error!\n");
		return 0;
	}

	q->el = el;

	q->next = p->next;
	p->next = q;

	return 0;
}

int popS(Position p) {
	Position temp = NULL;
	int el;

	if (p->next != NULL) {
		temp = p->next;
		el =temp->el;
		p->next = temp->next;
		free(temp);
	}

	return el;
}

int popR(Position p) {
	Position temp = NULL;
	int el;

	while(p->next->next != NULL)
		p = p->next;

	temp = p->next;
	el = temp->el;
	free(temp);
	p->next = NULL;

	return el;
}

int print(Position p) {
	if (p == NULL)
		puts("Empty!");

	while(p != NULL) {
		printf("%d ", p->el); 
		p = p->next;
	}

	printf("\n");

	return 0;
}