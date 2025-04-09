#include "Grid.h"
#include <fstream>
#include <cstdio>

CGrid::CGrid()
{
	InitGrid();
}

CGrid::CGrid(const string& filename)
{
	ReadFromFile_CStyle(filename);
}

void CGrid::InitGrid()
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
			Map[y][x] = CNode(y, x, RawMap[y][x]);
		}
	}
}

void CGrid::ReadFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file) {
		cerr << "���� ���� ����: " << filename << endl;
		return;
	}

	int rows, cols;
	file >> rows >> cols; // ���Ͽ� ��� ���� ���� ����Ǿ��ִٰ� ����
	Map.assign(rows, vector<CNode>(cols));

	int TempValue = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file >> TempValue;
			Map[i][j] = CNode(i, j, TempValue);
			if (TempValue == 3) {
				StartNode = &Map[i][j];
			}
			else if (TempValue == -3) {
				TargetNode = &Map[i][j];            
			}
		}
	}

	file.close();
}

void CGrid::ReadFromFile_CStyle(const string& Filename)
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

	Map.assign(rows, vector<CNode>(cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int TempValue = 0;
			int ret = fscanf_s(fp, "%d", &TempValue);
			Map[i][j] = CNode(i, j, TempValue);
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

void CGrid::PrintWallChar(int y, int x) {
	bool up = (y > 0)						&& (Map[y - 1][x].NodeType == 1);
	bool down = (y < Map.size() - 1)		&& (Map[y + 1][x].NodeType == 1);
	bool left = (x > 0)						&& (Map[y][x - 1].NodeType == 1);
	bool right = (x < Map[0].size() - 1)	&& (Map[y][x + 1].NodeType == 1);

	if (up && down && left && right) cout << "��";
	else if (up && left && !right && !down) cout << "��";
	else if (up && right && !left && !down) cout << "��";
	else if (down && left && !up && !right) cout << "��";
	else if (down && right && !up && !left) cout << "��";
	else if (left && right && !up && !down) cout << "��";
	else if (up && down && !left && !right) cout << "��";
	else if (up && down && left && !right) cout << "��";
	else if (up && down && right && !left) cout << "��";
	else if (left && right && up && !down) cout << "��";
	else if (left && right && down && !up) cout << "��";
	else if (left || right) cout << "��";
	else if (up || down ) cout << "��";
	else cout << '*';
}


void CGrid::PrintGrid()
{
	if (Map.size() <= 0) {
		cout << "Grid�� �ʱ�ȭ���� �ʾҽ��ϴ�." << endl;
		return;
	}

	for (int y = 0; y < Map.size(); y++) {
		for (int x = 0; x < Map[y].size(); x++) {
			if (Map[y][x].NodeType == 1) {
				//cout << "*";
				//PrintWallChar(y, x);
				cout << "��";
			}
			else if (Map[y][x].NodeType == -1) {
				cout << "��";
			}
			else if (Map[y][x].NodeType == 3) {
				cout << "��";
			}
			else if (Map[y][x].NodeType == -3) {
				cout << "��";
			}
			else {
				cout << "��";
			}
		}
		cout << endl;
	}
}
