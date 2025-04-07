#include <iostream>
#include "Grid.h"

using namespace std;

int main()
{
	//Grid StarGrid;
	Grid StarGrid("matrix.txt");

	StarGrid.PrintGrid();

	return 0;
}