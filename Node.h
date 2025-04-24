#pragma once

class CNode
{
public:
	CNode() : Row(0), Col(0), NodeType(0)
	{

	}
	CNode(const int Row, const int Col, int NodeType)
		: Row(Row), Col(Col), NodeType(NodeType)
	{

	}

	//int GetFCost() const { return GCost + HCost; }

	int Row;
	int Col;
	int NodeType;

	//int GCost = INT_MAX; // ���� ��忡�� �ش� �������� �ҿ�� �Ÿ�
	//int HCost = 0; // �ش� ��忡�� Ÿ�� �������� ���� �Ÿ�
	//CNode* ParentNode = nullptr;

	/*bool operator < (const CNode& n) const
	{
		if (this->GetFCost() < n.GetFCost())
			return true;
		else if(this->GetFCost() == n.GetFCost() && this->HCost < n.HCost)
			return true;
		else
			return false;
	}*/

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
struct NodeStateGreator
{
	const std::vector<std::vector<NodeState>>* CostPtr;
	bool operator()(const CNode* a, const CNode* b) const
	{
		const auto& Cost = *CostPtr;
		int FCostA = Cost[a->Row][a->Col].GCost + Cost[a->Row][a->Col].HCost;
		int FCostB = Cost[b->Row][b->Col].GCost + Cost[b->Row][b->Col].HCost;
					  
		int HCostA = Cost[a->Row][a->Col].HCost;
		int HCostB = Cost[b->Row][b->Col].HCost;

		// // f�� �������� �켱, f�� ������ h�� �������� �켱
		if (FCostA != FCostB)
		{
			return FCostA > FCostB;
		}

		return HCostA > HCostB;
	}
};


// min-heap
//struct NodePtrGreator
//{
//	bool operator()(const CNode* a, const CNode* b) const
//	{
//		// // f�� �������� �켱, f�� ������ h�� �������� �켱
//		if (a->GetFCost() != b->GetFCost())
//		{
//			return a->GetFCost() > b->GetFCost();
//		}
//
//		return a->HCost > b->HCost;
//	}
//};