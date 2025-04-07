#pragma once

class Node
{
public:
	Node() : row(0), col(0), NodeType(0)
	{

	}
	Node(const int row, const int col, int NodeType)
		: row(row), col(col), NodeType(NodeType)
	{

	}

	int row;
	int col;
	int NodeType;

};