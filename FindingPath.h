#pragma once
#include <unordered_set>
#include "Grid.h"
#include "Visualizer.h"

class CFindingPath
{
public:
	CFindingPath();

	void FindPath(CNode* StartNode, CNode* TargetNode);
	void DrawGrid();
	vector<CNode*>& GetStartNodes()
	{
		return Grid.GetStartNodes();
	}
	CNode* GetTargetNode()
	{
		return Grid.GetTargetNode();
	}

private:			  
	void RetracePath(CNode* StartNode, CNode* TargetNode);
	int GetDistanceCost(CNode* Start, CNode* End);

	CGrid Grid;
	CVisualizer Visualizer;
};