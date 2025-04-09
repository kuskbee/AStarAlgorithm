#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"

using namespace std;

class CGrid
{
public:
	CGrid();
	CGrid(const string& Filename);

	//void InitGrid();
	vector<CNode*> GetNeighbours(CNode* node);
	void ReadFromFile(const string& Filename);
	void ReadFromFile_CStyle(const string& Filename);
	void PrintGrid();
	void PrintWallChar(int y, int x);
	
private:
	vector<vector<CNode>> Map;

	CNode* StartNode = nullptr;
	CNode* TargetNode = nullptr;

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

public:
	CNode* GetStartNode() { return StartNode; }
	CNode* GetTargetNode() { return TargetNode; }
};