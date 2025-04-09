#include <iostream>
#include <conio.h>
#include "FindingPath.h"

using namespace std;

int main()
{
	CFindingPath fp;
	while (true)
	{
		system("cls");
		
		fp.DrawGrid();

		char c = _getch();
		if (c == 'f')
			fp.FindPath();
		else if (c == 'q')
			break;
	}

	return 0;
}