#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;
typedef struct node* Position;
typedef struct node{
	int exp;
	int coef;
	Position next;
}Node;

void Create(Position p, int exp, int coef);
void Print(Position p);
void Sum(Position p, Position q, Position r);
void ReadFromFile(char* fileName, Position p);
void SortUnos(Position p, int exp, int coef);
void Mnozi(Position p, Position q, Position r);
void SortSum(Position p);

int main()
{
	Node head1, head2, head3, head4;

	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;

	ReadFromFile("red1.txt", &head1);
	//printf("p(x) = ");
	Print(&head1);

	ReadFromFile("red2.txt", &head2);
	//printf("q(x) = ");
	Print(&head2);

	Sum(&head1, &head2, &head3);
	//printf("p(x) + q(x) = ");
	Print(&head3);
	
	Mnozi(&head1, &head2, &head4);
	SortSum(&head4);
	//printf("p(x) * q(x) = ");
	Print(&head4);

	return 0;
}

void Create(Position p, int exp, int coef) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	q->exp = exp;
	q->coef = coef;

	q->next = p->next;
	p->next = q;
}
void SortCreate(Position p, int exp, int coef) {
	while(p->next != NULL && p->next->exp > exp)
		p = p->next;

	Create(p, exp, coef);
	SortSum(p);
}
void Print(Position p) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	q = p->next;

	puts("--POLINOME--");

	while(q!=NULL) {
		printf("%dx^%d\t", q->coef, q->exp);
		q = q->next;
	}

	printf("\n");
}
void Sum(Position p, Position q, Position r) {
	Position temp = NULL;

	p = p->next;
	q = q->next;

	r->next = NULL;

	while(p!=NULL && q!=NULL) {

		if ( p->exp == q->exp ) {
			SortCreate(r, p->exp, p->coef + q->coef);
			p = p->next;
			q = q->next;
		}
			
		else if ( p->exp > q->exp ) {
			SortCreate(r, p->exp, p->coef);
			p = p->next;
		}

		else if ( p->exp < q->exp) {
			SortCreate(r, q->exp, q->coef);
			q = q->next;
		}
	}
	
	if (p!=NULL) 
		temp = p;

	else
		temp = q;

	while(temp!=NULL) {
		SortCreate(r, temp->exp, temp->coef);
		temp = temp->next;
	}
}
void ReadFromFile(char* fileName, Position p) {
	FILE *f;
	char line[100];
	int  a, b;

	f = fopen(fileName, "r");

	while(fgets(line, sizeof(line), f) != NULL) {
		sscanf(line, "%d %d", &a, &b);
		if ( b == 0) 
			continue;
		SortCreate(p, a, b);
	}
}
void Mnozi(Position p, Position q, Position r) {
	Position temp;

	p = p->next;
	q = q->next;
	temp = q;

	r->next = NULL;

	while(p!=NULL) {
		while(q!=NULL) {
			SortCreate(r, p->exp + q->exp, p->coef * q->coef);
			q = q->next;
		}
		q = temp;
		p = p->next;
	}
}
void SortSum(Position p) {
	Position q = NULL, temp = NULL;

	q = p->next;

	while(q->next!=NULL) {
		if ( q->exp == q->next->exp ) {
			q->coef+=q->next->coef;
			temp = q->next;
			q->next = q->next->next;
			free(temp);
		}

		else q = q->next;
	}
}