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

	int GCost = 0; // ���� ��忡�� �ش� �������� �ҿ�� �Ÿ�
	int HCost = 0; // �ش� ��忡�� Ÿ�� �������� ���� �Ÿ�
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