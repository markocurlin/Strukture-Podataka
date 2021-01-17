#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DIR_NAME_LENGTH 1024

struct dir;
typedef struct dir* Position;
typedef struct dir {
	char name[DIR_NAME_LENGTH];
	Position next;
	Position child;
} Dir;

struct stack;
typedef struct stack* Pos;
typedef struct stack {
	Position p;
	Pos next;
} Stack;

Position cddir(Position p, Pos q);
Position cd(Position p, Pos q);
int md(Position p);
Position pop(Pos q);
int push(Position p, Pos q);
int printList(Position p);
Position freeDir(Position p);
Position deleteDir(Position p, Pos q);

int main()
{
	Dir head;
	Position temp;
	Stack stack;
	int a;

	head.next = NULL;
	head.child = NULL;

	stack.next = NULL;
	stack.p = NULL;

	strcpy(head.name, "C:");

	temp = &head;

	do {
		puts("\n1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - izlaz");
		scanf("%d", &a); 
		switch(a) {
		case 1:
			md(temp);
			break;
		case 2:
			temp = cddir(temp, &stack);
			break;
		case 3:
			temp = cd(temp, &stack);
			break;
		case 4:
			printf("/%s/", temp->name);
			printList(temp);
			break;
		default:
			break;
		}
	}while(a != 5);

	temp = deleteDir(temp, &stack);

	return 0;
}

int md(Position p) {
	Position q = NULL;
	char name[DIR_NAME_LENGTH];

	puts("Enter name of directory: ");
	scanf("%s", name);

	q = (Position)malloc(sizeof(Dir));
	
	if (!q)
		perror("Error!");
	
	strcpy(q->name, name);
		
	q->next = p->child;
	p->child = q;
	q->child = NULL;

	return 0;
}

Position cddir(Position p, Pos q) {
	char name[DIR_NAME_LENGTH];
	Position temp = NULL;
	int br = 0, i = 0;

	temp = p->child;
	
	if ( temp == NULL ) {
		puts("Directory is empty!");
		return p;
	}

	puts("Enter name of directory: ");
	scanf("%s", name);

	while(temp != NULL && strcmp(temp->name, name) != 0) {
		temp = temp->next;
	}

	if ( temp == NULL ) {
		puts("Directory does not exist!");
		return p;
	}

	push(p, q);

	return temp;
}

Position cd(Position p, Pos q) {
	Position r = NULL;

	r = pop(q);

	if ( r == NULL ) 
		return p;

	return r;
}

int push(Position p, Pos q) {
	Pos r = NULL;

	r = (Pos)malloc(sizeof(Stack));

	r->p = p;

	r->next = q->next;
	q->next = r;

	return 0;
}

Position pop(Pos q) {
	Position r = NULL;
	Pos s = NULL;

	if (q->next != NULL) {
		r = q->next->p;
		s = q->next;
		q->next = s->next;
		free(s);
	}

	return r;
}

Position freeDir(Position p) {

	if (p == NULL)
		return NULL;
	
	p->child = freeDir(p->child);
	p->next = freeDir(p->next); 
	
	free(p);

	return NULL;
}

Position deleteDir(Position p, Pos q) {
	Position temp = p;

	while(q->next != NULL)
		temp = pop(q);

	temp = freeDir(temp->child);

	return temp;
}

int printList(Position p) {
	if (p == NULL)
		puts("\nEmpty list!");

	p = p->child;
	
	while(p != NULL) {
		printf("%s/", p->name);
		p = p->next;
	}

	return 0;
}