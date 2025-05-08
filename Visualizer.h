#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include <Windows.h>
#include "Node.h"
#include "MarkMsgQueue.h"

class CVisualizer
{
public:
	CVisualizer();
	virtual ~CVisualizer();

	void Initialize(std::vector<std::vector<CNode>>& Grid, size_t SizeX, size_t SizeY);
	
	std::vector<std::vector<CNode*>> GridMap;
	std::unordered_set<CNode*> OpenSet;
	std::unordered_set<CNode*> ClosedSet;
	std::unordered_set<CNode*> PathSet;

	void PumpAndDraw(size_t ExpectedDone);

	void DrawGridStep();
	void DrawNode(int x, int y, std::wstring Character);

	void ClearConsoleScreen();

	size_t GridSizeX = 10;
	size_t GridSizeY = 10;

	CMarkMsgQueue MsgQueue;

private:
	HANDLE ScreenHandles[2];
	int CurrentScreenIndex = 0;

};

