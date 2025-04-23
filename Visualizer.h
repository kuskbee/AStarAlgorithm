#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include "Node.h"

using namespace std;

class CVisualizer
{
public:
	void Initialize(vector<vector<CNode>>& Grid, size_t SizeX, size_t SizeY);
	
	vector<vector<CNode*>> GridMap;
	unordered_set<CNode*> OpenSet;
	unordered_set<CNode*> ClosedSet;
	unordered_set<CNode*> PathSet;

	void DrawGridStep();

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

};

