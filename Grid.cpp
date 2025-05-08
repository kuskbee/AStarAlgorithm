#include "Grid.h"
#include <fstream>
#include <cstdio>

CGrid::CGrid()
{
}

CGrid::CGrid(const std::string& filename)
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

std::vector<CNode*> CGrid::GetNeighbours(CNode* node)
{
	std::vector<CNode*> Neighbours;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			if(x == 0 && y == 0) continue; // 자기 자신

			int GridX = node->Col + x;
			int GridY = node->Row + y;

			if (GridX >= 0 && GridX < GridSizeX && GridY >= 0 && GridY < GridSizeY)
			{
				Neighbours.push_back(&Map[GridY][GridX]);
			}
		}
	}
	return Neighbours;
}

void CGrid::ReadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "파일 열기 실패: " << filename << std::endl;
		return;
	}

	int rows, cols;
	file >> rows >> cols; // 파일에 행과 열의 수가 저장되어있다고 가정
	Map.assign(rows, std::vector<CNode>(cols));
	GridSizeX = cols;
	GridSizeY = rows;

	int TempValue = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file >> TempValue;
			Map[i][j] = CNode(i, j, TempValue);
			if (TempValue == 3) {
				StartNodes.push_back(&Map[i][j]);
			}
			else if (TempValue == -3) {
				TargetNode = &Map[i][j];            
			}
		}
	}

	file.close();
}

void CGrid::ReadFromFile_CStyle(const std::string& Filename)
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

	Map.assign(rows, std::vector<CNode>(cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int TempValue = 0;
			int ret = fscanf_s(fp, "%d", &TempValue);
			Map[i][j] = CNode(i, j, TempValue);
			if (TempValue == 3) {
				StartNodes.push_back(&Map[i][j]);
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

void CGrid::PrintGrid()
{
	if (Map.size() <= 0) {
		std::cout << "Grid가 초기화되지 않았습니다." << std::endl;
		return;
	}

	for (int y = 0; y < Map.size(); y++) {
		for (int x = 0; x < Map[y].size(); x++) {
			if (Map[y][x].NodeType == 1) { // 벽
				//cout << "*";
				//PrintWallChar(y, x);
				std::cout << "■";
			}
			else if (Map[y][x].NodeType == -1) { // 경로
				std::cout << "★";
			}
			else if (Map[y][x].NodeType == 3) { // 시작점
				std::cout << "ⓢ";
			}
			else if (Map[y][x].NodeType == -3) { // 끝점
				std::cout << "ⓔ";
			}
			else {
				std::cout << "　";
			}
		}
		std::cout << std::endl;
	}
}
