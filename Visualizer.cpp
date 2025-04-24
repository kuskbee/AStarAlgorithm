#include "Visualizer.h"
#include <thread>
#include <chrono>

using Clock = std::chrono::steady_clock;
using MilliSeconds = std::chrono::milliseconds;
constexpr MilliSeconds DeltaTick = MilliSeconds(16);

void CVisualizer::Initialize(vector<vector<CNode>>& Grid, size_t SizeX, size_t SizeY)
{
	GridSizeX = SizeX;
	GridSizeY = SizeY;

	GridMap.assign(SizeY, vector<CNode*>(SizeX, nullptr));

	for (size_t y = 0; y < SizeY; y++)
	{
		for (size_t x = 0; x < SizeX; x++)
		{
			CNode* Origin = &Grid[y][x];
			GridMap[y][x] = Origin;
		}
	}
}

void CVisualizer::PumpAndDraw(size_t ExpectedDone)
{
	//auto NextTick = Clock::now();

	size_t DoneCnt = 0;
	while (DoneCnt < ExpectedDone)
	{
		CMarkMsgQueue::MarkMsg Msg;
		MsgQueue.WaitPop(Msg);
		if (Msg.Type == CMarkMsgQueue::Mark::Open)
		{
			OpenSet.insert(GridMap[Msg.Row][Msg.Col]);
		}
		else if (Msg.Type == CMarkMsgQueue::Mark::Close)
		{
			ClosedSet.insert(GridMap[Msg.Row][Msg.Col]);
		}
		else if (Msg.Type == CMarkMsgQueue::Mark::Path)
		{
			PathSet.insert(GridMap[Msg.Row][Msg.Col]);
		}
		else if (Msg.Type == CMarkMsgQueue::Mark::Done)
		{
			++DoneCnt;
		}

		DrawGridStep();
		/*auto Now = Clock::now();

		if (Now >= NextTick)
		{
			DrawGridStep();
			NextTick += DeltaTick;
		}*/
	}
}

void CVisualizer::DrawGridStep()
{
	system("cls");
	size_t GridSizeX = this->GridSizeX;
	size_t GridSizeY = this->GridSizeY;
	for (int y = 0; y < GridSizeY; y++)
	{
		for (int x = 0; x < GridSizeX; x++)
		{
			CNode* Node = GridMap[y][x];
			if (PathSet.count(Node)) cout << "¡Ú";
			else if (ClosedSet.count(Node)) cout << "¡Ü";
			else if (OpenSet.count(Node)) cout << "¡Û";
			else if (Node->NodeType == 1) cout << "¡á";
			else if (Node->NodeType == 3) cout << "¨ß";
			else if (Node->NodeType == -3) cout << "¨à";
			else	cout << "¡¡";
		}
		cout << endl;
	}
	//this_thread::sleep_for(chrono::milliseconds(1));
}
