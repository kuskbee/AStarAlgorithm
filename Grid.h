#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"

class CGrid
{
public:
	CGrid();
	CGrid(const std::string& Filename);

	//void InitGrid();
	std::vector<CNode*> GetNeighbours(CNode* node);
	void ReadFromFile(const std::string& Filename);
	void ReadFromFile_CStyle(const std::string& Filename);
	void PrintGrid();

	std::vector<std::vector<CNode>> Map;
private:
	std::vector<CNode*> StartNodes;
	CNode* TargetNode = nullptr;

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

public:
	std::vector<CNode*>& GetStartNodes() { return StartNodes; }
	CNode* GetTargetNode() { return TargetNode; }
	size_t GetGridSizeX() { return GridSizeX; }
	size_t GetGridSizeY() { return GridSizeY; }
};