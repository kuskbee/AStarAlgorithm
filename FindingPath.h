#pragma once
#include "Grid.h"


class CFindingPath
{
public:
	CFindingPath();

	void FindPath();
	void DrawGrid();
	
private:
	void RetracePath();
	int GetDistanceCost(CNode* Start, CNode* End);


	CGrid Grid;
};