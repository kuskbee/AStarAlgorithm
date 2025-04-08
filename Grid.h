#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"

using namespace std;

class Grid
{
public:
	Grid();
	Grid(const string& Filename);

	void InitGrid();
	void ReadFromFile(const string& Filename);
	void ReadFromFile_CStyle(const string& Filename);
	void PrintGrid();
	void PrintWallChar(int y, int x);
	
private:
	vector<vector<Node>> Map;

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

};