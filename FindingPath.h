#pragma once
#include "Grid.h"


class CFindingPath
{
public:
	CFindingPath();


	vector<CNode> OpenList;
	vector<CNode> ClosedList;


	CGrid Grid;
};