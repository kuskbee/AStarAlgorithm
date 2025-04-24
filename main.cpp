#include <iostream>
#include <conio.h>
#include <thread>
#include "FindingPath.h"
#include "Visualizer.h"

using namespace std;

int main()
{
	CGrid Grid;
	Grid.ReadFromFile_CStyle("matrix.txt");
	CVisualizer Visualizer;
	Visualizer.Initialize(Grid.Map, Grid.GetGridSizeX(), Grid.GetGridSizeY());

	vector<thread> workers;

	while (true)
	{
		char c = _getch();
		if (c == 'f')
		{
			vector<CNode*> StartNodes = Grid.GetStartNodes();
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
			std::cout << "All paths finished." << std::endl;
			break;
		}
		else if (c == 'q')
		{
			break;
		}
	}

	return 0;
}