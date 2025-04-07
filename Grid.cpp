#include "Grid.h"
#include <fstream>
#include <cstdio>

Grid::Grid()
{
	InitGrid();
}

Grid::Grid(const string& filename)
{
	ReadFromFile_CStyle(filename);
}

void Grid::InitGrid()
{
	vector<vector<int>> RawMap = {
		{1,1,1,1,1, 1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,1,1,1,1, 1,1,1,1,1},
	};

	GridSizeX = 10;
	GridSizeY = 10;

	for (int y = 0; y < GridSizeY; y++) {
		for (int x = 0; x < GridSizeX; x++) {
			Map[y][x] = Node(y, x, RawMap[y][x]);
		}
	}
}

void Grid::ReadFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file) {
		cerr << "���� ���� ����: " << filename << endl;
		return;
	}

	int rows, cols;
	file >> rows >> cols; // ���Ͽ� ��� ���� ���� ����Ǿ��ִٰ� ����
	Map.assign(rows, vector<Node>(cols));

	int TempValue = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file >> TempValue;
			Map[i][j] = Node(i, j, TempValue);
		}
	}

	file.close();
}

void Grid::ReadFromFile_CStyle(const string& Filename)
{
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, "matrix.txt", "r");
	if (err != 0 || fp == nullptr) {
		perror("���� ���� ����");
		return;
	}

	int rows, cols;
	if (fscanf_s(fp, "%d %d", &rows, &cols) != 2) {
		perror("��� ũ�� �б� ����");
		fclose(fp);
		return;
	}

	Map.assign(rows, vector<Node>(cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int TempValue = 0;
			int ret = fscanf_s(fp, "%d", &TempValue);
			Map[i][j] = Node(i, j, TempValue);
			if (ret == EOF) {
				fclose(fp);
				break;
			}
			else if (ret != 1) {
				perror("��� ������ �б� ����");
				fclose(fp);
				return;
			}
		}
	}
	fclose(fp);
}

void Grid::PrintGrid()
{
	if (Map.size() <= 0) {
		cout << "Grid�� �ʱ�ȭ���� �ʾҽ��ϴ�." << endl;
		return;
	}

	for (int y = 0; y < Map.size(); y++) {
		for (int x = 0; x < Map[y].size(); x++) {
			if (Map[y][x].NodeType == 1) {
				cout << "*";
			}
			else if (Map[y][x].NodeType == -1) {
				cout << "@";
			}
			else if (Map[y][x].NodeType == 3) {
				cout << "S";
			}
			else if (Map[y][x].NodeType == -3) {
				cout << "E";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}
