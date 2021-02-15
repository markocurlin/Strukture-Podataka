#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct node;
typedef struct node* Position;
typedef struct node {
	int coef;
	int exp;
	Position next;
} Node;

int print(Position p);
Position createNode(int exp, int coef);
int sortUnos(Position p, int exp, int coef);
int readFromFile(Position p, char* fileName);
int sum(Position p, Position q, Position r);
int multiply(Position p, Position q, Position r);
int sort(Position p);

int main()
{
	Node head1, head2, head3, head4;

	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;

	readFromFile(&head1, "red1.txt");
	print(head1.next);

	readFromFile(&head2, "red2.txt");
	print(head2.next);

	sum(&head1, &head2, &head3);
	print(head3.next);

	multiply(&head1, &head2, &head4);
	print(head4.next);
	sort(&head4);
	print(head4.next);

	return 0;
}

Position createNode(int exp, int coef) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	if (q == NULL)
		perror("Error!\n");

	q->coef = coef;
	q->exp = exp;

	return q;
}

int sortUnos(Position p, int exp, int coef) {
	Position q = NULL;

	q = createNode(exp, coef);

	while(p->next != NULL && p->next->exp > exp)
		p = p->next;

	q->next = p->next;
	p->next = q;

	return 0;
}

int readFromFile(Position p, char* fileName) {
	FILE* f;
	int coef, exp;

	f = fopen(fileName, "r");

	if ( f == NULL ) {
		perror("Error opening file!\n");
		return 0;
	}

	while(!feof(f)) {
		fscanf(f, "%d %d", &coef, &exp);
		sortUnos(p, coef, exp);
	}

	return 0;
}

int sum(Position p, Position q, Position r) {
	Position temp = NULL;

	p = p->next;
	q = q->next;
	r->next = NULL;

	while(p && q != NULL) {
		if (p->exp == q->exp) {
			sortUnos(r, p->exp, p->coef);
			p = p->next;
			q = q->next;
		}

		else if (p->exp > q->exp) {
			sortUnos(r, p->exp, p->coef);
			p = p->next;
		}

		else if (p->exp < q->exp) {
			sortUnos(r, q->exp, q->coef);
			q = q->next;
		}
	}

	if ( p == NULL )
		temp = q;
	else
		temp = p;

	while(temp != NULL) {
		sortUnos(r, temp->exp, temp->coef);
		temp = temp->next;
	}

	return 0;
}

int multiply(Position p, Position q, Position r) {
	Position temp = NULL;

	p = p->next;
	q = q->next;
	temp = q;
	r->next = NULL;
	
	while(p != NULL) {
		while( q != NULL ) {
			sortUnos(r, p->exp + q->exp, p->coef*q->coef);
			q = q->next;
		}
		q = temp;
		p = p->next;
	}

	return 0;
}

int sort(Position p) {
	Position temp = NULL;
	Position q = NULL;

	q = p->next;
	
	while(q->next != NULL) {
		if ( q->exp == q->next->exp ) {
			q->coef += q->next->coef;
			temp = q->next;
			q->next = temp->next;
			free(temp);
		}

		else
			q = q->next;
	}

	return 0;
}

int print(Position p) {
	while(p != NULL) {
		printf("%dx^%d\t", p->coef, p->exp);
		p = p->next;
	}

	printf("\n");

	return 0;
}