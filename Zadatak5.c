#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct node;
typedef struct node* Position;
typedef struct node {
	int x;
	Position next;
}Node;

int sortUnos(Position p, int x);
int create(Position p, int x);
int deleteX(Position p);
int printList(Position p);
int unija(Position p, Position q, Position r);
int presjek(Position p, Position q, Position r);

int main() {
	int x, y, i;
	Node head1, head2, head3, head4;

	head1.next = head2.next = head3.next = head4.next = NULL;

	printf("Insert number of elements = ");
	scanf("%d", &y);

	for( i = 0; i<y; i++ ) {
		printf("%d. element = ", i+1);
		scanf("%d", &x);
		sortUnos(&head1, x);
	}

	printf("Insert number of elements = ");
	scanf("%d", &y);

	for( i = 0; i<y; i++ ) {
		printf("%d. element = ", i+1);
		scanf("%d", &x);
		sortUnos(&head2, x);
	}

	unija(&head1, &head2, &head3);
	presjek(&head1, &head2, &head4);

	printf("First list: ");
	printList(&head1);
	printf("Second list: ");
	printList(&head2);
	printf("Unija: ");
	printList(&head3);
	printf("Presjek: ");
	printList(&head4);

	return 0;
}

int sortUnos(Position p, int x) {

	while( p->next != NULL && p->next->x < x )
		p = p->next;

	create(p , x);
	deleteX(p);

	return 0;
}

int create(Position p, int x) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Node));

	q->x = x;
	q->next = p->next;
	p->next = q;

	return 0;
}

int deleteX(Position p) {
	Position q = NULL;
	Position temp = NULL;

	q = p->next;

	while( q->next != NULL ) {
		if ( q->x == q->next->x ) {
			temp = q->next;
			q->next = q->next->next;
			free(temp);
		}
		else
			q = q->next;
	}

	return 0;
}

int printList(Position p) {
	Position q = NULL;

	q = p->next;

	while( q != NULL ) {
		printf("%d ", q->x);
		q = q->next;
	}

	puts(" ");

	return 0;
}

int unija(Position p, Position q, Position r) {
	Position temp = NULL;

	p = p->next;
	q = q->next;

	while( p!=NULL && q!=NULL ) {
		if ( p->x == q->x ) {
			sortUnos(r, p->x);
			p = p->next;
			q = q->next;
		}
		else if ( p->x > q->x ) {
			sortUnos(r, p->x);
			p = p->next;
		}
		else if ( p->x < q->x ) {
			sortUnos(r, q->x);
			q = q->next;
		}
	}

	if ( p != NULL )
		temp = p;
	else
		temp = q;

	while( temp != NULL ) {
		sortUnos(r, temp->x);
		temp = temp->next;
	}

	return 0;
}

int presjek(Position p, Position q, Position r) {
	Position temp = NULL;

	p = p->next;
	q = q->next;

	temp = q;

	while( p != NULL ) {
		while( q != NULL ) {
			if ( p->x == q->x ) {
				sortUnos(r, p->x);
			}
			q = q->next;
		}
		q = temp;
		p = p->next;
	}

	return 0;
}