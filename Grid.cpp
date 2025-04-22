#include "Grid.h"
#include <fstream>
#include <cstdio>

CGrid::CGrid()
{
}

CGrid::CGrid(const string& filename)
{
	ReadFromFile_CStyle(filename);
}

//void CGrid::InitGrid()
//{
//	vector<vector<int>> RawMap = {
//		{1,1,1,1,1, 1,1,1,1,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,0,0,0,0, 0,0,0,0,1},
//		{1,1,1,1,1, 1,1,1,1,1},
//	};
//
//	GridSizeX = 10;
//	GridSizeY = 10;
//
//	for (int y = 0; y < GridSizeY; y++) {
//		for (int x = 0; x < GridSizeX; x++) {
//			Map[y][x] = CNode(y, x, RawMap[y][x]);
//		}
//	}
//}

vector<CNode*> CGrid::GetNeighbours(CNode* node)
{
	vector<CNode*> Neighbours;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			if(x == 0 && y == 0) continue; // 자기 자신

			int GridX = node->col + x;
			int GridY = node->row + y;

			if (GridX >= 0 && GridX < GridSizeX && GridY >= 0 && GridY < GridSizeY)
			{
				Neighbours.push_back(&Map[GridY][GridX]);
			}
		}
	}
	return Neighbours;
}

void CGrid::ReadFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file) {
		cerr << "파일 열기 실패: " << filename << endl;
		return;
	}

	int rows, cols;
	file >> rows >> cols; // 파일에 행과 열의 수가 저장되어있다고 가정
	Map.assign(rows, vector<CNode>(cols));
	GridSizeX = cols;
	GridSizeY = rows;

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
		perror("파일 열기 실패");
		return;
	}

	int rows, cols;
	if (fscanf_s(fp, "%d %d", &rows, &cols) != 2) {
		perror("행렬 크기 읽기 실패");
		fclose(fp);
		return;
	}
	GridSizeX = cols;
	GridSizeY = rows;

	Map.assign(rows, vector<CNode>(cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int TempValue = 0;
			int ret = fscanf_s(fp, "%d", &TempValue);
			Map[i][j] = CNode(i, j, TempValue);
			if (TempValue == 3) {
				StartNode = &Map[i][j];
			}
			else if (TempValue == -3) {
				TargetNode = &Map[i][j];
			}
			if (ret == EOF) {
				fclose(fp);
				break;
			}
			else if (ret != 1) {
				perror("행렬 데이터 읽기 실패");
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

	if (up && down && left && right) cout << "┼";
	else if (up && left && !right && !down) cout << "┘";
	else if (up && right && !left && !down) cout << "└";
	else if (down && left && !up && !right) cout << "┐";
	else if (down && right && !up && !left) cout << "┌";
	else if (left && right && !up && !down) cout << "─";
	else if (up && down && !left && !right) cout << "│";
	else if (up && down && left && !right) cout << "┤";
	else if (up && down && right && !left) cout << "├";
	else if (left && right && up && !down) cout << "┴";
	else if (left && right && down && !up) cout << "┬";
	else if (left || right) cout << "─";
	else if (up || down ) cout << "│";
	else cout << '*';
}


void CGrid::PrintGrid()
{
	if (Map.size() <= 0) {
		cout << "Grid가 초기화되지 않았습니다." << endl;
		return;
	}

	for (int y = 0; y < Map.size(); y++) {
		for (int x = 0; x < Map[y].size(); x++) {
			if (Map[y][x].NodeType == 1) { // 벽
				//cout << "*";
				//PrintWallChar(y, x);
				cout << "■";
			}
			else if (Map[y][x].NodeType == -1) { // 경로
				cout << "★";
			}
			else if (Map[y][x].NodeType == 3) { // 시작점
				cout << "ⓢ";
			}
			else if (Map[y][x].NodeType == -3) { // 끝점
				cout << "ⓔ";
			}
			else {
				cout << "　";
			}
		}
		cout << endl;
	}
}
