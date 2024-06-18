#pragma once
#include <vector>
#include <map>
#include "Position.h"
#include "Definiciones.h"
#include "Colors.h"
class Block
{
public:
	void Render(int offsetX, int offsetY);
	void Rotate();
	void Move(int rows, int columns);
	void UndoRotate();
	Block();
	~Block();
	int id;
	std::map<int, std::vector<Position>> cells;
	std::vector<Position> GetCellPositions();
private:
	int cellSize, rotationState;
	std::vector<Color> colors;
	int rowOffset, columnOffset;
};

