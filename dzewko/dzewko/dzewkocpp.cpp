#include <iostream>
#include <conio.h>
#include <memory>

//calloc zeruje zarezerwowana pamiec
using namespace std;
int elementy_stosu;
enum Type
{
	INT,
	DOUBLE,
	CHAR,
	STOS,
};
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
	void *element;
	struct tree *left;
	struct tree *right;
	Type type;
};
template<class T>
tree *addNode(struct tree *korzen, void *n, Type type)
{
	double nowy;
	double wezel;
	int compareChar = 0;
	if (korzen == NULL)
	{
		korzen = (struct tree*)malloc(sizeof(struct tree*));
		korzen->element = n;
		korzen->left = NULL;
		korzen->right = NULL;
		korzen->type = type;
		return korzen;
	}
	else
	{
		if ((korzen->type == INT || korzen->type == DOUBLE || korzen->type == CHAR) && (type == INT || type == DOUBLE || type == CHAR))
		{

				if (korzen->type == INT) wezel = *static_cast<int*>(korzen->element);
				else wezel =  *static_cast<double*>(korzen->element);

				if (type == DOUBLE) nowy = *static_cast<double*>(n);
				else nowy = *static_cast<int*>(n);

			 
			if (korzen->type == CHAR && type == CHAR) //przypadek gdy porwnujemy 2 chary
			{
				
				char *w = static_cast<char*>(korzen->element);
				char *no = static_cast<char*>(n);
				if (strcmp(no, w) > 0 ) compareChar = 1;//nowy wiekszy, idzie na prawo
				else compareChar = 2;//nowy mniejszy idzie na lewo
			}
			

			if ((korzen->type == CHAR && type != CHAR) || ((double)wezel >= (double)nowy && (korzen->type != CHAR && type != CHAR)) || compareChar == 2) //mniejszy-lewa strona
			{			
				if (korzen->left == NULL)
				{
					korzen->left = (struct tree*)malloc(sizeof(struct tree*));
					korzen->left->element = n;
					korzen->left->right = NULL;
					korzen->left->left = NULL;
					korzen->left->type = type;
				}
				else addNode<T>(korzen->left, n, type);
			}
			else if ((korzen->type != CHAR && type == CHAR) || ((double)wezel < (double)nowy && (korzen->type != CHAR && type != CHAR)) || compareChar == 1) //wiekszy-prawa strona
			{
				if (korzen->right == NULL)
				{
					korzen->right = (struct tree*)malloc(sizeof(struct tree*));
					korzen->right->element = n;
					korzen->right->right = NULL;
					korzen->right->left = NULL;
					korzen->right->type = type;
				}
				else addNode<T>(korzen->right, n, type);
			}
			else 
			{

			}
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

	//ifologia do wypisania
	if (korzen->type == INT)
	{
		int w = *static_cast<int*>(korzen->element);
		printf("%i(int), ", w);
		printf("\n");
	}
	if (korzen->type == DOUBLE)
	{
		double w = *static_cast<double*>(korzen->element);
		printf("%f(double), ", w);
		printf("\n");
	}
	if (korzen->type == CHAR)
	{
		char *w = static_cast<char*>(korzen->element);
		printf("%s(char*), ", w);
		printf("\n");
	}

	if (korzen->right != NULL) inOrder(korzen->right);	
}


struct tree2
{
	Type type;
	void *t;
};
void addNode2(tree2 *a, void *liczba, Type type)
{

	if (a->type == INT && type == DOUBLE)
	{
		int wezel = *static_cast<int*>(a->t);
		double nowy = *static_cast<double*>(liczba);

		if ((double)wezel > nowy)cout << wezel;
		else cout << nowy;

	}


}
int main()
{
	tree2 *a = (struct tree2*)malloc(sizeof(struct tree2*));
	
	int b = 10;
	double c = 4.1;
	void *w = &b;
	char *cz = "abz";
	char *cz2 = "aba";
	a->t = w;
	a->type = INT;
	
	stack *s = (struct stack*)malloc(sizeof(struct stack*));

	tree *korzen;
	korzen = NULL;
	//uwazac na zmiane adresow zmiennych
	korzen = addNode<int>(korzen, &b, INT);
	addNode<char*>(korzen, cz, CHAR);
	addNode<char*>(korzen, cz2, CHAR);
	int z = 15;
	addNode<int>(korzen, &z, INT);
	addNode<double>(korzen, &c, DOUBLE);
	double h = 11.11;
	addNode<double>(korzen, &h, DOUBLE);
	
	

	inOrder(korzen);
	_getch();
	return 0;
}