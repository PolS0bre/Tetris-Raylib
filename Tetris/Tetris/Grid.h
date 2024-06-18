#pragma once
#include <vector>
#include "raylib.h"
class Grid
{
public:
	Grid();
	~Grid();
	void Initialize();
	void Print();
	void Render();
	bool IsBlockOutside(int row, int col), IsCellEmpty(int row, int col);
	int ClearFullRows();
	int grid[20][10];
private:
	bool IsRowFull(int row);
	void ClearRow(int row), MoveRowDown(int row, int numRows);
	int numRows, numCols, cellSize;
	std::vector<Color> colors;
};

