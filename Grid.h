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

	vector<vector<CNode>> Map;
private:
	vector<CNode*> StartNodes;
	CNode* TargetNode = nullptr;

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

public:
	vector<CNode*>& GetStartNodes() { return StartNodes; }
	CNode* GetTargetNode() { return TargetNode; }
	size_t GetGridSizeX() { return GridSizeX; }
	size_t GetGridSizeY() { return GridSizeY; }
};