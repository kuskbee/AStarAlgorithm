#include "FindingPath.h"
#include <queue>

using namespace std;

CFindingPath::CFindingPath(CGrid& Grid, CMarkMsgQueue* MsgQueue)
	:Grid(Grid), MsgQueue(MsgQueue)
{
}

void CFindingPath::FindPath(CNode* StartNode, CNode* TargetNode)
{
	int SizeX = Grid.GetGridSizeX();
	int SizeY = Grid.GetGridSizeY();
	vector<vector<NodeState>> Cost (SizeY, vector<NodeState>(SizeX));
	NodeStateGreator Cmp{ &Cost };
	priority_queue<CNode*, vector<CNode*>, NodeStateGreator> OpenListQueue(Cmp); // �������� (��� ������)
	unordered_set<CNode*> OpenListSet;
	unordered_set<CNode*> ClosedListSet;

	Cost[StartNode->Row][StartNode->Col].GCost = 0;
	OpenListQueue.push(StartNode);
	OpenListSet.insert(StartNode);
	if (MsgQueue) {
		MsgQueue->Push({CMarkMsgQueue::Mark::Open, StartNode->Row, StartNode->Col });
	}

	while (OpenListQueue.size() > 0) {
		CNode* CurrentNode = OpenListQueue.top();
		//Visualizer.DrawGridStep();
		
		OpenListQueue.pop();
		OpenListSet.erase(CurrentNode);
		ClosedListSet.insert(CurrentNode);
		Cost[CurrentNode->Row][CurrentNode->Col].bOpenList = false;
		Cost[CurrentNode->Row][CurrentNode->Col].bClosedList = true;
		if (MsgQueue) {
			MsgQueue->Push({ CMarkMsgQueue::Mark::Close, CurrentNode->Row, CurrentNode->Col });
		}

		if (CurrentNode == TargetNode) {
			RetracePath(StartNode, TargetNode, Grid, Cost);
			if (MsgQueue) {
				MsgQueue->Push({ CMarkMsgQueue::Mark::Done, -1, -1 });
			}
			return;
		}

		vector<CNode*> Neighbours = Grid.GetNeighbours(CurrentNode);
		for (CNode* Node : Neighbours)
		{
			// ���̰ų� �̹� Ž���� ����� ��ŵ
			if (Node->NodeType == 1 || ClosedListSet.count(Node))
				continue;

			// �̿������� Gcost�� Hcost�� ����Ͽ� Open List�� �߰�
			int CurrentGCost = Cost[CurrentNode->Row][CurrentNode->Col].GCost;
			int newCost = CurrentGCost + GetDistanceCost(CurrentNode, Node);

			int NodeGCost = Cost[Node->Row][Node->Col].GCost;
			if (newCost < NodeGCost || !OpenListSet.count(Node))
			{
				Cost[Node->Row][Node->Col].GCost = newCost;
				Cost[Node->Row][Node->Col].HCost = GetDistanceCost(Node, TargetNode);
				Cost[Node->Row][Node->Col].ParentCol = CurrentNode->Col;
				Cost[Node->Row][Node->Col].ParentRow = CurrentNode->Row;

				if (!OpenListSet.count(Node)) {
					OpenListQueue.push(Node);
					OpenListSet.insert(Node);
					Cost[Node->Row][Node->Col].bOpenList = true;
					if (MsgQueue) {
						MsgQueue->Push({ CMarkMsgQueue::Mark::Open, Node->Row, Node->Col });
					}
				}
			}
		}
	}
}

void CFindingPath::DrawGrid()
{
	Grid.PrintGrid();
}

void CFindingPath::RetracePath(CNode* StartNode, CNode* TargetNode,
								CGrid& Grid,
								vector<vector<NodeState>>& Costs)
{
	CNode* CurrentNode = TargetNode;

	while (CurrentNode != StartNode)
	{
		if (CurrentNode != TargetNode)
		{
			//CurrentNode->NodeType = -1;
			if (MsgQueue) {
				MsgQueue->Push({ CMarkMsgQueue::Mark::Path, CurrentNode->Row, CurrentNode->Col });
			}
		}
		int ParentRow = Costs[CurrentNode->Row][CurrentNode->Col].ParentRow;
		int ParentCol = Costs[CurrentNode->Row][CurrentNode->Col].ParentCol;
		CurrentNode = &Grid.Map[ParentRow][ParentCol];
	}

	//Visualizer.DrawGridStep();
}

int CFindingPath::GetDistanceCost(CNode* Start, CNode* End)
{
	int DistX = abs(End->Col - Start->Col);
	int DistY = abs(End->Row - Start->Row);

	// �Ÿ��� ª������ �������� �밢�� �̵��ϰ�, ���� �Ÿ��� ���� �̵�
	if (DistX > DistY) {
		return 14 * DistY + 10 * (DistX - DistY);
	}

	return 14 * DistX + 10 * (DistY - DistX);	
}


