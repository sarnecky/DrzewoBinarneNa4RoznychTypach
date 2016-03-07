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
	//root = (struct stack*)malloc(sizeof(struct stack*));
	root = new stack;
	root->next = New;
	root->elementy_stosu = e;
	root->number = element;

	return root;
}

void pop(stack *root)
{
	
	int element = 0;

	struct stack *p;
	int e = root->elementy_stosu--;
	if (root != NULL)
	{
		p = root;
		root = root->next; //tutaj wierzcholek staje sie poprzednim elementem
		//free(p);
		delete(p);
	}

	if (root!=NULL)
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
bool porownajStosy(stack *s1, stack*s2) //zakladamy ze maja ta sama dlugosc
{
	int i = 0;
	int e = s1->elementy_stosu; 
	while (i != e)
	{
		if (s1->number != s2->number) return false;
		else
		{
			s1 = s1->next;
			s2 = s2->next;
		}
		i++;
	}
	return true;
}

struct tree
{
	void *element;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
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
		//korzen = (struct tree*)malloc(sizeof(struct tree*));
		korzen = new tree;
		korzen->element = n;
		korzen->left = NULL;
		korzen->right = NULL;
		korzen->type = type;
		korzen->parent = korzen;
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
					//korzen->left = (struct tree*)malloc(sizeof(struct tree*));
					korzen->left = new tree;
					korzen->left->element = n;
					korzen->left->right = NULL;
					korzen->left->left = NULL;
					korzen->left->type = type;
					korzen->left->parent = korzen;
				}
				else addNode(korzen->left, n, type);
			}
			else if ((korzen->type != CHAR && type == CHAR && korzen->type != STOS) ||
				((double)wezel < (double)nowy && (korzen->type != CHAR && type != CHAR)) ||
				compareChar == 1 || compareStack == 1 || (korzen->type != STOS && type == STOS)) //wiekszy-prawa strona
			{
				if (korzen->right == NULL)
				{
					//korzen->right = (struct tree*)malloc(sizeof(struct tree*));
					korzen->right = new tree;
					korzen->right->element = n;
					korzen->right->right = NULL;
					korzen->right->left = NULL;
					korzen->right->type = type;
					korzen->right->parent = korzen;
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

tree *search(tree *korzen, void *n, Type type)
{
	//funkcja zwraca adres gdzie znajduje sie dana wartoœæ w drzewie
	double nowy; //ten ktorego szukam
	double wezel; //ten w ktorym sie obecnie znajduje
	int compareChar = 0;
	int compareStack = 0;
	if (korzen == NULL)
		return korzen;


	//schodzimy wg³¹b drzewa
	if ((korzen->type == INT || korzen->type == DOUBLE || korzen->type == CHAR || korzen->type == STOS) && (type == INT || type == DOUBLE || type == CHAR || type == STOS))
	{
		//przypadki int i double
		if (korzen->type == INT) wezel = *static_cast<int*>(korzen->element);
		else wezel = *static_cast<double*>(korzen->element);

		if (type == DOUBLE) nowy = *static_cast<double*>(n);
		else nowy = *static_cast<int*>(n);

		if (type == korzen->type)
		{
			if (type == INT || type == DOUBLE)
			{
				if ((double)wezel == (double)nowy)
					return korzen;
			}
		}
			

		//przypadek char*
		if (korzen->type == CHAR && type == CHAR) //przypadek gdy porwnujemy 2 chary
		{

			char *w = static_cast<char*>(korzen->element); //element sprawdzany
			char *no = static_cast<char*>(n); //nowy element
			if (strcmp(no, w) > 0) compareChar = 1;//nowy wiekszy, idzie na prawo
			else if (strcmp(no, w) < 0)compareChar = 2;//nowy mniejszy idzie na lewo
			else  //przypadek gdy ciagi znakow sa rowne
			{
				return korzen;
			}
		}

		//przypadek stosu
		if (korzen->type == STOS && type == STOS) //przypadek gdy porownujemy 2 stosy
		{
			stack *w = static_cast<stack*>(korzen->element);
			stack *no = static_cast<stack*>(n);
			if (w->elementy_stosu < no->elementy_stosu) compareStack = 1; //ilosc elemetow nowego stosu jest wieksza wiec wstwiamy go do prawego wezla
			else if (w->elementy_stosu > no->elementy_stosu) compareStack = 2;
			else
			{
				if (porownajStosy(w, no))
					return korzen;
			}
		}

		//logika wyszukiwania

		if ((korzen->type == CHAR && type != CHAR && type != STOS) ||
			((double)wezel >= (double)nowy && (korzen->type != CHAR && type != CHAR && korzen->type != STOS && type != STOS)) ||
			compareChar == 2 || compareStack == 2 || (korzen->type == STOS && type != STOS)) //mniejszy-lewa strona
		{
			return search(korzen->left, n, type); //schodzimy w lewo stronê
		}
		else if ((korzen->type != CHAR && type == CHAR && korzen->type != STOS) ||
			((double)wezel < (double)nowy && (korzen->type != CHAR && type != CHAR)) ||
			compareChar == 1 || compareStack == 1 || (korzen->type != STOS && type == STOS)) //wiekszy-prawa strona
		{
			return search(korzen->right, n, type); //schodzimy w praw¹ stronê
		}
		else{}
	}

}
tree *searchMin(tree *korzen)
{
	while (korzen->left != NULL)
		korzen = korzen->left;
	return korzen;
}
tree *nastepnik(tree *korzen)
{
	if (korzen->right != NULL)
		return searchMin(korzen);
	tree *tmp = korzen->parent;
	while (tmp != NULL && tmp->left != korzen)
	{
		korzen = tmp;
		tmp = tmp->parent;
	}
	return tmp;
}
tree *deleteNode(struct tree *korzen, void *n, Type type)
{
	tree *DoUsuniecia = search(korzen, n, type); //szuka danego elementu do usuniecia
	tree *y, *x;
	if (DoUsuniecia == NULL) return DoUsuniecia;
	if (DoUsuniecia->left == NULL || DoUsuniecia->right == NULL)
		y = DoUsuniecia;
	else y = nastepnik(DoUsuniecia);

	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		korzen->parent = x; //korzen->root !!!!!
	else
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	if (y != DoUsuniecia)
		DoUsuniecia->element = y->element;
	return y;
}
void interfejs()
{
	int b = 10,l;
	char *napis;
	tree *korzen;
	korzen = NULL;
	korzen = addNode(korzen, &b, INT);
	int k, ilosc;
	int *w,a0;
	double *wd,a1;
	int *z;
	stack *s = NULL;
	cout << "Nacisnij klawisz\n";
	cout << "1. int, 2. double, 3. char*, 4. stos, 5. podglad drzewa, 6. usun dany wezel \n";
	while (cin >> k)
	{
		system("cls");

		switch (k)
		{
		case 1:
			cout << "1. Znaki rozne lub 2. takie same | ilosc znakow\n";
			cin >> k >> ilosc;
			w = new int[ilosc];
			if (k == 2)
			{
				cout << "Jaki znak ?";
				cin >> k;
				for (int i = 0; i < ilosc; i++)
				{
					int w = k;
					addNode(korzen, &w, INT);
				}
			}
			else
			{
				for (int i = 0; i < ilosc; i++)
				{
					
					cout << "Jaki znak ?";
					cin >> w[i];
					addNode(korzen, &w[i], INT);
				}
			}
			system("cls");
			inOrder(korzen);
			break;
		case 2:
			cout << "1. Znaki rozne lub 2. takie same | ilosc znakow\n";
			cin >> k >> ilosc;
			wd = new double[ilosc];
			if (k == 2)
			{
				cout << "Jaki znak ?";
				cin >> k;
				for (int i = 0; i < ilosc; i++)
				{
					int w = k;
					addNode(korzen, &wd, DOUBLE);
				}
			}
			else
			{
				for (int i = 0; i < ilosc; i++)
				{

					cout << "Jaki znak ?";
					cin >> wd[i];
					addNode(korzen, &wd[i], DOUBLE);
				}
			}
			system("cls");
			inOrder(korzen);
			break;
		case 3:
			cout << "Podaj napis\n";
			napis = new char;
			cin >> napis;
			addNode(korzen, napis, CHAR);
			inOrder(korzen);
			break;
		case 4:
			cout << "Stos: ile elementow\n";
			cin >> ilosc;
			cout << "\n";
			cout << "Stos: Podawaj kolejne elementy\n";
			w = new int[ilosc];
			s = NULL;
			for (int i = 0; i < ilosc; i++)
			{

				cout << "Jaki znak ?";
				cin >> k;
				s = push(k, s);

			}
			system("cls");
			addNode(korzen, s, STOS);
			inOrder(korzen);
			break;
		case 5:

			inOrder(korzen);
			break;
		case 6:
			cout << "Podaj typ zmiennej 0. INT 1.DOUBLE 2.CHAR* 3.STOS \n";
			cin >> k;
			cout << "Podaj wartosc zmiennej/stosu \n";
			if (k == 0)
			{
				cin >> a0;
				delete(deleteNode(korzen, &a0, (Type)k));
			}
			if (k == 1)
			{
				cin >> a1;
				delete(deleteNode(korzen, &a1, (Type)k));
			}
			if (k == 2)
			{
				napis = new char;
				cin >> napis;
				delete(deleteNode(korzen, napis, (Type)k));
			}
			if (k == 3)
			{
				cout << "Stos: ile elementow\n";
				cin >> ilosc;
				cout << "\n";
				cout << "Stos: Podawaj kolejne elementy stosu\n";
				w = new int[ilosc];
				s = NULL;
				for (int i = 0; i < ilosc; i++)
				{

					cout << "Jaki znak ?";
					cin >> l;
					s = push(l, s);

				}
				system("cls");
				delete(deleteNode(korzen, s, (Type)k));
				inOrder(korzen);
			}
			system("cls");
			inOrder(korzen);
			break;

		}
		cout << "Nacisnij klawisz\n";
		cout << "1. int, 2. double, 3. char*, 4. stos, 5. podglad drzewa, 6.usun element\n";
	}

}	
int main()
{
	interfejs();
	_getch();
	return 0;
}