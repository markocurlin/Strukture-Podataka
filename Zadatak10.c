#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATA_SIZE 11
#define FILE_NAME_SIZE 1024

struct node;
typedef struct node* NodePosition;
typedef struct node {
	char data[DATA_SIZE];
	NodePosition right;
	NodePosition left;
}Node;

struct list;
typedef struct list* ListPosition;
typedef struct list {
	NodePosition data;
	ListPosition next;
}List;

NodePosition createNode(char* data);
ListPosition createListNode(NodePosition data);
int push(ListPosition head, NodePosition data);
int pushBack(ListPosition head, NodePosition data);
NodePosition pop(ListPosition head);
int isNumber(char* str);
int toInfixList(ListPosition head, NodePosition current);
NodePosition readPostfixFromFile(char* fileName);
NodePosition deleteNode(NodePosition data);
int deleteList(ListPosition head);
int printInfixToFile(char* fileName, ListPosition head);

int main()
{
	NodePosition root = NULL;
	ListPosition p = NULL;
	List infixResult;
	char fileName[FILE_NAME_SIZE] = {0};

	infixResult.next = NULL;

	printf("Insert name of file: ");
	scanf("%s", fileName);
	
	root = readPostfixFromFile(fileName);

	if ( root == NULL )
		return 0;

	toInfixList(&infixResult, root);

	printInfixToFile(fileName, &infixResult);

	root = deleteNode(root);
	deleteList(&infixResult);
	
	return 0;
}

NodePosition createNode(char* data) {
	NodePosition p = NULL;

	p = (NodePosition)malloc(sizeof(Node));

	if ( p == NULL ) {
		perror("Error!\n");
		return NULL;
	}

	strcpy(p->data, data);
	p->right = NULL;
	p->left = NULL;

	return p;
}
ListPosition createListNode(NodePosition data) {
	ListPosition p = NULL;

	p = (ListPosition)malloc(sizeof(List));

	if ( p == NULL) {
		perror("Error!\n");
		return NULL;
	}

	p->data = data;
	p->next = NULL;

	return p;
}
int push(ListPosition head, NodePosition data) {
	ListPosition node = NULL;

	node = createListNode(data);
	
	if ( node == NULL )
		return -1;

	node->next = head->next;
	head->next = node;

	return 0;
}
int isNumber(char* str) {
	int number = 0;

	if ( sscanf(str, " %d", &number) == 1 )
		return 1;
	else
		return 0;
}
NodePosition pop(ListPosition head) {
	ListPosition temp = head->next;
	NodePosition result = NULL;

	if (temp == NULL)
		return NULL;

	result = temp->data;
	head->next = temp->next;	
	free(temp);

	return result;
}
int pushBack(ListPosition head, NodePosition data) {
	ListPosition p = head;

	while(p->next != NULL)
		p = p->next;

	return push(head, data);
}
int toInfixList(ListPosition head, NodePosition current) {
	if ( current == NULL )
		return 1;

	toInfixList(head, current->right);
	pushBack(head, current);
	toInfixList(head, current->left);

	return 0;
}
NodePosition readPostfixFromFile(char* fileName) {
	FILE* fp;
	char readString[DATA_SIZE] = {0};
	NodePosition result = NULL;
	List head;

	head.next = NULL;
	head.data = NULL;

	fp = fopen(fileName, "r");

	if ( fp == NULL ) {
		puts("Error opening file!\n");
		return NULL;
	}

	while(!feof(fp)) {
		NodePosition node = NULL;
		fscanf(fp, " %s", readString);
		node = createNode(readString);

		if ( node == NULL ) {
			fclose(fp);
			return NULL;
		}

		if (isNumber(node->data)) {
			push(&head, node);
		}

		else {
			node->right = pop(&head);

			if ( node->right == NULL ) {
				puts("Postfix isn't right, please check it!\n");
				return NULL;
			}

			node->left = pop(&head);

			if ( node->left == NULL ) {
				puts("Postfix isn't right, please check it!\n");
				return NULL;
			}

			push(&head, node);
		}
	}

	result = pop(&head); 

	if ( result == NULL ) {
		printf("File is empty!\n");
		return NULL;
	}

	if ( pop(&head) != NULL ) {
		puts("Postfix isn't right, please check it!\n");
		return NULL;
	}

	fclose(fp);

	return result;
}
NodePosition deleteNode(NodePosition data) {
	if ( data == NULL )
		return NULL;
	
	data->right = deleteNode(data->right);
	data->left = deleteNode(data->left);
	
	free(data);

	return NULL;
}
int deleteList(ListPosition head) {
	ListPosition temp = NULL;

	if ( head->next == NULL ) {
		free(head);
		return 0;
	}

	while(head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	
	return 0;
}
int printInfixToFile(char* fileName, ListPosition head) {
	FILE* fp = NULL;
	ListPosition p = NULL;

	fp = fopen(fileName, "w");

	if ( fp == NULL ) {
		perror("File doesn't exists!\n");
		return 0;
	}

	for ( p = head->next; p != NULL; p = p->next)
		fprintf(fp, " %s", p->data->data);
	
	return 0;
}