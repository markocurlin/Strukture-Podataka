#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node;
typedef struct node* Position;
typedef struct node {
	int el;
	Position next;
}Node;

int push(Position p, int el) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));
	q->el = el;

	q->next = p->next;
	p->next = q;

	return 0;
}

int print(Position p) {
	p = p->next;

	while(p != NULL) {
		printf("%d ", p->el);
		p = p->next;
	}

	puts(" ");
	
	return 0;
}

//stog
int popS(Position p) {
	Position q = NULL;
	int el;

	if ( p->next != NULL ) {
		q = p->next;
		el = q->el;
		p->next = q->next;

		free(q);
	}

	return el;
}

//red
int popR(Position p) {
	Position q = NULL, prev = NULL;
	int el;

	if ( p->next != NULL ) {
		q = p->next;
		prev = p;
		while(q->next != NULL) {
			prev = q;
			q=q->next;
		}

		el = q->el;
		prev->next = q->next;
		free(q);
	}

	return el;
}

int main()
{
	Node head1, head2;
	int el, i;

	head1.next = NULL; //stog
	head2.next = NULL; //red

	srand((unsigned)time(NULL));

	//stog
	for(i = 0; i < 6; i++) {
		el = rand()%89+10;
		push(&head1, el);
	}

	printf("Stog: ");
	print(&head1);

	for(i = 0; i < 6; i++) {
		popS(&head1);
		print(&head1);
	}
	
	puts("-------------------------------\n");

	//red
	for(i = 0; i < 6; i++) {
		el = rand()%89+10;
		push(&head2, el);
	}

	printf("Red: ");
	print(&head2);

	for(i = 0; i < 6; i++) {
		popR(&head2);
		print(&head2);
	}

	return 0;
}