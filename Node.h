#pragma once

class CNode
{
public:
	CNode() : row(0), col(0), NodeType(0)
	{

	}
	CNode(const int row, const int col, int NodeType)
		: row(row), col(col), NodeType(NodeType)
	{

	}

	int GetFCost() const { return GCost + HCost; }

	int row;
	int col;
	int NodeType;

	int GCost = INT_MAX; // 시작 노드에서 해당 노드까지의 소요된 거리
	int HCost = 0; // 해당 노드에서 타겟 노드까지의 예상 거리
	CNode* ParentNode = nullptr;

	bool operator < (const CNode& n) const
	{
		if (this->GetFCost() < n.GetFCost())
			return true;
		else if(this->GetFCost() == n.GetFCost() && this->HCost < n.HCost)
			return true;
		else
			return false;
	}

};

struct NodeState
{
	int GCost = INT_MAX;
	int HCost = 0;
	int ParentRow = -1;
	int ParentCol = -1;

	bool bOpenList = false;
	bool bClosedList = false;
};



// min-heap
struct NodePtrGreator
{
	bool operator()(const CNode* a, const CNode* b) const
	{
		// // f가 작을수록 우선, f가 같으면 h가 작을수록 우선
		if (a->GetFCost() != b->GetFCost())
		{
			return a->GetFCost() > b->GetFCost();
		}

		return a->HCost > b->HCost;
	}
};