#include <iostream>
#include <conio.h>
#include <memory>

//calloc zeruje zarezerwowana pamiec
using namespace std;
int elementy_stosu;

struct stack
{
	int number;
	struct stack *next;
	
}*top = NULL;

void push(int element)
{
	elementy_stosu++;
	struct stack *New;
	New = top;//nowy element staje sie wierzcholkiem
	top = (struct stack*)malloc(sizeof(struct stack*));
	top->number = element;
	top->next = New;
}

void pop()
{
	//przy "CRT detected that the application wrote to memory after end of heap buffer" dac Ignore i dziala
	int element = 0;
	struct stack *p;
	elementy_stosu--;
	if (top != NULL)
	{
		p = top;
		top = top->next; //tutaj wierzcholek staje sie poprzednim elementem
		free(p);
	}
}
void wypisz()
{
	int i = 0;
	struct stack *p;
	p = top;
	while (i != elementy_stosu)
	{
		printf("%i, ", p->number);
		p = p->next;
		i++;
	}
}

struct tree
{
	int element;
	struct tree *left;
	struct tree *right;
};

tree *addNode(struct tree *korzen, int n)
{
	if (korzen == NULL)
	{
		korzen = (struct tree*)malloc(sizeof(struct tree*));
		korzen->element = n;
		korzen->left = NULL;
		korzen->right = NULL;
		return korzen;
	}
	else
	{
		if (korzen->element >= n) //mniejszy-lewa strona
		{
			if (korzen->left == NULL)
			{
				korzen->left = (struct tree*)malloc(sizeof(struct tree*));
				korzen->left->element = n;
				korzen->left->right = NULL;
				korzen->left->left = NULL;
			}
			else addNode(korzen->left, n);
		}
		else //wiekszy-prawa strona
		{
			if (korzen->right == NULL)
			{
				korzen->right = (struct tree*)malloc(sizeof(struct tree*));
				korzen->right->element = n;
				korzen->right->right = NULL;
				korzen->right->left = NULL;
			}
			else addNode(korzen->right, n);
		}
	}
}
tree *a(tree *korzen)
{
	korzen = (struct tree*)malloc(sizeof(struct tree*));
	cout << korzen->element;
	return korzen;
}
void inOrder(tree *korzen)
{
	if (korzen->left != NULL) inOrder(korzen->left);
	printf("%i, ", korzen->element);
	if (korzen->right != NULL) inOrder(korzen->right);	
}
int main()
{

	
	tree *korzen;
	korzen = NULL;
	korzen=addNode(korzen, 2);
	addNode(korzen, 1);
	addNode(korzen, 5);
	addNode(korzen, 7);
	addNode(korzen, 10);
	addNode(korzen, 0);

	inOrder(korzen);
	_getch();
	return 0;
}