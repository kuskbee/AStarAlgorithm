#pragma once
#include "Grid.h"
#include <unordered_set>


class CFindingPath
{
public:
	CFindingPath();

	void FindPath();
	void DrawGrid();
	void DrawGridStep(CNode* CurrentNode, 
					  const unordered_set<CNode*>& OpenListSet,
					  const unordered_set<CNode*>& CloseListSet);

private:			  
	void RetracePath();
	int GetDistanceCost(CNode* Start, CNode* End);


	CGrid Grid;
};