#include <iostream>
#include <conio.h>
#include <memory>

//calloc zeruje zarezerwowana pamiec
using namespace std;

int main()
{
	char *lancuch;
	lancuch = (char *)malloc(10);
	strcpy(lancuch, "hi");
	printf("\nLancunch zawiera napis:%s", lancuch);
	free(lancuch);

	_getch();
	return 0;
}