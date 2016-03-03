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

int main()
{
	_getch();
	return 0;
}