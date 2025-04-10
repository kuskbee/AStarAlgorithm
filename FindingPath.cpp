#include "FindingPath.h"
#include <queue>
#include <unordered_set>

using namespace std;

CFindingPath::CFindingPath()
{
	Grid.ReadFromFile_CStyle("matrix.txt");
}

void CFindingPath::FindPath()
{
	CNode* StartNode = Grid.GetStartNode();
	CNode* TargetNode = Grid.GetTargetNode();
	priority_queue<CNode*, vector<CNode*>, greater<CNode*>> OpenListQueue; // �������� (��� ������)
	unordered_set<CNode*> OpenListSet;
	unordered_set<CNode*> ClosedListSet;
	OpenListQueue.push(StartNode);
	OpenListSet.insert(StartNode);

	while (OpenListQueue.size() > 0) {
		CNode* CurrentNode = OpenListQueue.top();
		OpenListQueue.pop();
		OpenListSet.erase(CurrentNode);
		ClosedListSet.insert(CurrentNode);

		if (CurrentNode == TargetNode) {
			RetracePath();
			return;
		}

		vector<CNode*> Neighbours = Grid.GetNeighbours(CurrentNode);
		for (CNode* Node : Neighbours)
		{
			// ���̰ų� �̹� Ž���� ����� ��ŵ
			if (Node->NodeType == 1 || ClosedListSet.count(Node))
				continue;

			// �̿������� Gcost�� Hcost�� ����Ͽ� Open List�� �߰�
			int newCost = CurrentNode->GCost + GetDistanceCost(CurrentNode, Node);

			if (newCost < Node->GCost || !OpenListSet.count(Node))
			{
				Node->GCost = newCost;
				Node->HCost = GetDistanceCost(Node, TargetNode);
				Node->ParentNode = CurrentNode;

				if (!OpenListSet.count(Node)) {
					OpenListQueue.push(Node);
					OpenListSet.insert(Node);
				}
			}
		}
	}
}

void CFindingPath::DrawGrid()
{
	Grid.PrintGrid();
}

void CFindingPath::RetracePath()
{
	CNode* StartNode = Grid.GetStartNode();
	CNode* TargetNode = Grid.GetTargetNode();
	CNode* CurrentNode = TargetNode;

	while (CurrentNode != StartNode)
	{
		CurrentNode->NodeType = -1;
		
		CurrentNode = CurrentNode->ParentNode;
	}
}

int CFindingPath::GetDistanceCost(CNode* Start, CNode* End)
{
	int DistX = abs(End->col - Start->col);
	int DistY = abs(End->row - Start->row);

	// �Ÿ��� ª������ �������� �밢�� �̵��ϰ�, ���� �Ÿ��� ���� �̵�
	if (DistX > DistY) {
		return 14 * DistY + 10 * (DistX - DistY);
	}

	return 14 * DistX + 10 * (DistY - DistX);	
}


