#include <iostream>
#include <conio.h>
#include <memory>

//calloc zeruje zarezerwowana pamiec
using namespace std;

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
	int elementy_stosu;
};
stack *push(int element, stack *root)
{
	int e;
	if (root == NULL) e = 0;
	else e = root->elementy_stosu;
	e++;

	struct stack *New;
	New = root;
	root = (struct stack*)malloc(sizeof(struct stack*));
	root->next = New;
	root->elementy_stosu = e;
	root->number = element;

	return root;
}

void pop(stack *root)
{
	//przy "CRT detected that the application wrote to memory after end of heap buffer" dac Ignore i dziala
	int element = 0;

	struct stack *p;
	int e = root->elementy_stosu--;
	if (root != NULL)
	{
		p = root;
		root = root->next; //tutaj wierzcholek staje sie poprzednim elementem
		free(p);
	}
	root->elementy_stosu = e;

}

void wypisz(stack *root)
{
	int i = 0;
	struct stack *p;
	p = root;
	int e = root->elementy_stosu;
	printf("{ ");
	while (i != e)
	{
		printf("%i, ", p->number);
		p = p->next;
		i++;
	}
	printf("} Stos");
	printf("\n");
}


struct tree
{
	void *element;
	struct tree *left;
	struct tree *right;
	Type type;
};
tree *addNode(struct tree *korzen, void *n, Type type)
{
	double nowy;
	double wezel;
	int compareChar = 0;
	int compareStack= 0;
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
		if ((korzen->type == INT || korzen->type == DOUBLE || korzen->type == CHAR || korzen->type == STOS) && (type == INT || type == DOUBLE || type == CHAR || type == STOS))
		{

				if (korzen->type == INT) wezel = *static_cast<int*>(korzen->element);
				else wezel =  *static_cast<double*>(korzen->element);

				if (type == DOUBLE) nowy = *static_cast<double*>(n);
				else nowy = *static_cast<int*>(n);

			 
			if (korzen->type == CHAR && type == CHAR) //przypadek gdy porwnujemy 2 chary
			{
				
				char *w = static_cast<char*>(korzen->element); //element sprawdzany
				char *no = static_cast<char*>(n); //nowy element
				if (strcmp(no, w) > 0 ) compareChar = 1;//nowy wiekszy, idzie na prawo
				else compareChar = 2;//nowy mniejszy idzie na lewo
			}
			
			if (korzen->type == STOS && type == STOS) //przypadek gdy porownujemy 2 stosy
			{
				stack *w = static_cast<stack*>(korzen->element);
				stack *no = static_cast<stack*>(n);
				if (w->elementy_stosu < no->elementy_stosu) compareStack = 1; //ilosc elemetow nowego stosu jest wieksza wiec wstwiamy go do prawego wezla
				else compareStack = 2;
			}

			if ((korzen->type == CHAR && type != CHAR && type != STOS) ||
				((double)wezel >= (double)nowy && (korzen->type != CHAR && type != CHAR && korzen->type != STOS && type != STOS)) ||
				compareChar == 2 || compareStack == 2 || (korzen->type == STOS && type != STOS)) //mniejszy-lewa strona
			{			
				if (korzen->left == NULL)
				{
					korzen->left = (struct tree*)malloc(sizeof(struct tree*));
					korzen->left->element = n;
					korzen->left->right = NULL;
					korzen->left->left = NULL;
					korzen->left->type = type;
				}
				else addNode(korzen->left, n, type);
			}
			else if ((korzen->type != CHAR && type == CHAR && korzen->type != STOS) ||
				((double)wezel < (double)nowy && (korzen->type != CHAR && type != CHAR)) ||
				compareChar == 1 || compareStack == 1 || (korzen->type != STOS && type == STOS)) //wiekszy-prawa strona
			{
				if (korzen->right == NULL)
				{
					korzen->right = (struct tree*)malloc(sizeof(struct tree*));
					korzen->right->element = n;
					korzen->right->right = NULL;
					korzen->right->left = NULL;
					korzen->right->type = type;
				}
				else addNode(korzen->right, n, type);
			}
			else 
			{

			}
		}
		
	}
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
	if (korzen->type == STOS)
	{
		stack *s = static_cast<stack*>(korzen->element);
		wypisz(s);

	}

	if (korzen->right != NULL) inOrder(korzen->right);	
}

int main()
{
	int b = 10;
	double c = 4.1;
	void *w = &b;
	char *cz = "abz";
	char *cz2 = "aba";
	stack *s = NULL;
	s=push(2,s);
	s=push(3,s);
	s=push(5,s);
	//wypisz(s);
	stack *s2 = NULL;
	s2=push(5, s2);
	s2=push(9, s2);
	///wypisz(s2);
	tree *korzen;
	korzen = NULL;
	//uwazac na zmiane adresow zmiennych
	korzen = addNode(korzen, &b, INT);
	addNode(korzen, cz, CHAR);
	addNode(korzen, cz2, CHAR);
	int z = 15;
	addNode(korzen, &z, INT);
	addNode(korzen, &c, DOUBLE);
	double h = 11.11;
	addNode(korzen, &h, DOUBLE);
	addNode(korzen, s, STOS);
	
	addNode(korzen, s2, STOS);
	
	

	inOrder(korzen);
	_getch();
	return 0;
}