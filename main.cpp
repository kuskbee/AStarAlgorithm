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
		{
			vector<CNode*> StartNodes = fp.GetStartNodes();
			CNode* TargetNode = fp.GetTargetNode();
			for(auto SNode : StartNodes)
			{
				fp.FindPath(SNode, TargetNode);
			}
			break;
		}
		else if (c == 'q')
		{
			break;
		}
	}

	return 0;
}