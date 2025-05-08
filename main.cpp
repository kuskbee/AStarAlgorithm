#include <iostream>
#include <conio.h>
#include <thread>
#include "FindingPath.h"
#include "Visualizer.h"

int main()
{
	CGrid Grid;
	Grid.ReadFromFile_CStyle("matrix.txt");
	CVisualizer Visualizer;
	Visualizer.Initialize(Grid.Map, Grid.GetGridSizeX(), Grid.GetGridSizeY());

	std::vector<std::thread> workers;

	while (true)
	{
		char c = _getch();
		if (c == 'f')
		{
			std::vector<CNode*> StartNodes = Grid.GetStartNodes();
			CNode* TargetNode = Grid.GetTargetNode();
			for(auto* SNode : StartNodes)
			{
				workers.emplace_back([&, SNode] 
					{
						CFindingPath fp(Grid, &Visualizer.MsgQueue);
						fp.FindPath(SNode, TargetNode);
					});		
			}

			Visualizer.PumpAndDraw(workers.size());

			for (auto& th : workers)
			{
				th.join();
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