#pragma once
#include <unordered_set>
#include "Grid.h"
#include "MarkMsgQueue.h"

class CFindingPath
{
public:
	CFindingPath(CGrid& Grid, CMarkMsgQueue* MsgQueue);

	void FindPath(CNode* StartNode, CNode* TargetNode);
	void DrawGrid();

private:			  
	void RetracePath(CNode* StartNode, CNode* TargetNode, 
					CGrid& Grid,
		std::vector<std::vector<NodeState>>& Costs);
	int GetDistanceCost(CNode* Start, CNode* End);

	CGrid& Grid;
	CMarkMsgQueue* MsgQueue = nullptr;
};