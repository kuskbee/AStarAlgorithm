#include "Visualizer.h"
#include <thread>
#include <chrono>


void CVisualizer::Initialize(vector<vector<CNode>>& Grid, size_t SizeX, size_t SizeY)
{
	GridSizeX = SizeX;
	GridSizeY = SizeY;

	GridMap.assign(SizeY, vector<CNode*>(SizeX, nullptr));

	for (size_t y = 0; y < SizeY; y++)
	{
		for (size_t x = 0; x < SizeX; x++)
		{
			CNode* Origin = &Grid[y][x];
			GridMap[y][x] = Origin;
		}
	}
}

void CVisualizer::DrawGridStep()
{
	system("cls");
	size_t GridSizeX = this->GridSizeX;
	size_t GridSizeY = this->GridSizeY;
	for (int y = 0; y < GridSizeY; y++)
	{
		for (int x = 0; x < GridSizeX; x++)
		{
			CNode* Node = GridMap[y][x];
			if (PathSet.count(Node)) cout << "¡Ú";
			else if (ClosedSet.count(Node)) cout << "¡Ü";
			else if (OpenSet.count(Node)) cout << "¡Û";
			else if (Node->NodeType == 1) cout << "¡á";
			else if (Node->NodeType == 3) cout << "¨ß";
			else if (Node->NodeType == -3) cout << "¨à";
			else	cout << "¡¡";
		}
		cout << endl;
	}
	this_thread::sleep_for(chrono::milliseconds(100));
}
