#include<stdio.h>
#include<stdlib.h>

struct tree;
typedef struct tree* Node;
typedef struct tree* Position;
typedef struct tree {
	int el;
	Node l_child;
	Node r_child;
}Tree;

Node createRoot(Node p);
Node insert(Node p, int el);
Node find(Node p, int el);
Node findMin(Node p);
Node findMax(Node p);
Node deleteEl(Node p, int el);
int print(Node p);

int main()
{
	Tree tree;
	Node root = &tree;

	root = createRoot(root);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 9);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 18);

	print(root);

	puts(" ");

	printf("Element 4 is on: %d\n", find(root, 4));
	printf("Minimum %d is on: %d\n", findMin(root)->el, findMin(root));
	printf("Maximum %d is on: %d\n", findMax(root)->el, findMax(root));
	
	root = deleteEl(root, 2);
	root = deleteEl(root, 7);

	print(root);
}


Node createRoot(Node p) {
	if (p != NULL)
		return NULL;
	else {
		createRoot(p->r_child);
		createRoot(p->l_child);
		free(p);
	}
	return NULL;
}

Node insert(Node p, int el) {
	if (p == NULL) {
		p = (Node)malloc(sizeof(Tree));
		if (!p)
			perror("Error!");
		p->el = el;
		p->r_child = NULL;
		p->l_child = NULL;
	}
	else if (p->el < el)
		p->r_child = insert(p->r_child, el);
	else
		p->l_child = insert(p->l_child, el);

	return p;
}

int print(Node p) {
	if (p != NULL) {
		print(p->l_child);
		printf("%d ", p->el);
		print(p->r_child);
	}

	return 0;
}

Node find(Node p, int el) {
	if (p == NULL) {
		puts("Element does not exist!");
		return NULL;
	}

	else if (p->el < el)
		return find(p->r_child, el);

	else if (p->el > el)
		return find(p->l_child, el);
	else
		return p;
}
Node findMin(Node p) {
	if (p == NULL) {
		puts("Element does not exist!");
		return NULL;
	}
	else if (p->l_child == NULL)
		return p;
	else
		return findMin(p->l_child);
}
Node findMax(Node p) {
	if (p != NULL) {
		while(p->r_child != NULL) {
			p = p->r_child;
		}
		return p;
	}
	else
		return p;
}

Node deleteEl(Node p, int el) {
	Node temp = NULL;

	if (p == NULL)
		puts("Element does not exist!");
	else if ( p->el < el )
		p->r_child = deleteEl(p->r_child, el);
	else if (p->el > el)
		p->l_child = deleteEl(p->l_child, el);
	else if (p->r_child && p->l_child != NULL) {
		temp = findMin(p->r_child);
		p->el = temp->el;
		p->r_child = deleteEl(p->r_child, el);
	}
	else {
		temp = p;
		if (p->l_child == NULL)
			p = p->r_child;
		else
			p = p->l_child;
		free(temp);
	}
	return p;
}