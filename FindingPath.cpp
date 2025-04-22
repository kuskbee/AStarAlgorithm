#include "FindingPath.h"
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

CFindingPath::CFindingPath()
{
	Grid.ReadFromFile_CStyle("matrix.txt");
}

void CFindingPath::FindPath()
{
	CNode* StartNode = Grid.GetStartNode();
	CNode* TargetNode = Grid.GetTargetNode();
	priority_queue<CNode*, vector<CNode*>, NodePtrGreator> OpenListQueue; // �������� (��� ������)
	unordered_set<CNode*> OpenListSet;
	unordered_set<CNode*> ClosedListSet;

	StartNode->GCost = 0;
	OpenListQueue.push(StartNode);
	OpenListSet.insert(StartNode);

	while (OpenListQueue.size() > 0) {
		CNode* CurrentNode = OpenListQueue.top();
		DrawGridStep(CurrentNode, OpenListSet, ClosedListSet);

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

void CFindingPath::DrawGridStep(CNode* CurrentNode, 
								const unordered_set<CNode*>& OpenListSet,
								const unordered_set<CNode*>& CloseListSet)
{
	system("cls");
	size_t GridSizeX = Grid.GetGridSizeX();
	size_t GridSizeY = Grid.GetGridSizeY();
	for (int y = 0; y < GridSizeY; y++)
	{
		for (int x = 0; x < GridSizeX; x++)
		{
			CNode& Node = Grid.Map[y][x];
			if (&Node == CurrentNode)	cout << "��";
			else if (CloseListSet.count(&Node)) cout << "��";
			else if (OpenListSet.count(&Node)) cout << "��";
			else if (Node.NodeType == 1) cout << "��";
			else if (Node.NodeType == 3) cout << "��";
			else if (Node.NodeType == -3) cout << "��";
			else	cout << "��";
		}
		cout << endl;
	}
	this_thread::sleep_for(chrono::milliseconds(500));
}

void CFindingPath::RetracePath()
{
	CNode* StartNode = Grid.GetStartNode();
	CNode* TargetNode = Grid.GetTargetNode();
	CNode* CurrentNode = TargetNode;

	while (CurrentNode != StartNode)
	{
		if (CurrentNode != TargetNode)
		{
			CurrentNode->NodeType = -1;
		}
		
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


