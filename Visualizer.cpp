#include "Visualizer.h"
#include <thread>
#include <chrono>

using Clock = std::chrono::steady_clock;
using MilliSeconds = std::chrono::milliseconds;
constexpr MilliSeconds DeltaTick = MilliSeconds(16);

CVisualizer::CVisualizer()
{
	ScreenHandles[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	ScreenHandles[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CurrentScreenIndex = 0;
}

CVisualizer::~CVisualizer()
{
	CloseHandle(ScreenHandles[0]);
	CloseHandle(ScreenHandles[1]);
}

void CVisualizer::Initialize(std::vector<std::vector<CNode>>& Grid, size_t SizeX, size_t SizeY)
{
	GridSizeX = SizeX;
	GridSizeY = SizeY;

	GridMap.assign(SizeY, std::vector<CNode*>(SizeX, nullptr));

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

		if (DoneCnt < ExpectedDone)
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
	ClearConsoleScreen();
	size_t GridSizeX = this->GridSizeX;
	size_t GridSizeY = this->GridSizeY;
	for (int y = 0; y < GridSizeY; y++)
	{
		for (int x = 0; x < GridSizeX; x++)
		{
			CNode* Node = GridMap[y][x];
			std::wstring Shape = L"¡¡";
			if (PathSet.count(Node)) Shape = L"¡Ú";
			else if (ClosedSet.count(Node)) Shape = L"¡Ü";
			else if (OpenSet.count(Node)) Shape = L"¡Û";
			else if (Node->NodeType == 1) Shape = L"¡á";
			else if (Node->NodeType == 3)
				Shape = L"¨ß";
			else if (Node->NodeType == -3)
				Shape = L"¨à";
			else	Shape = L"¡¡";

			DrawNode(x, y, Shape);
		}
		//std::cout << std::endl;
	}
	//this_thread::sleep_for(chrono::milliseconds(1));

	SetConsoleActiveScreenBuffer(ScreenHandles[CurrentScreenIndex]);
	CurrentScreenIndex++;
	CurrentScreenIndex %= 2;
}

void CVisualizer::DrawNode(int x, int y, std::wstring Character)
{
	SetConsoleCursorPosition(ScreenHandles[CurrentScreenIndex], COORD{ (short)(x * 2), (short)(y) });

	WriteConsole(ScreenHandles[CurrentScreenIndex], Character.c_str(), Character.size(), NULL, NULL);
}

void CVisualizer::ClearConsoleScreen()
{
	DWORD DW;
	FillConsoleOutputCharacter(ScreenHandles[CurrentScreenIndex], ' ', GridSizeX * (GridSizeY + 1), COORD{ 0, 0 }, &DW);
}
