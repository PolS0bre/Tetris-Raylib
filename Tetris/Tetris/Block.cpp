#include "Block.h"
#include <iostream>

void Block::Render(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles) {
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Rotate()
{
	rotationState++;
	if (rotationState == (int)cells.size()) {
		rotationState = 0;
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::UndoRotate()
{
	rotationState--;
	if (rotationState < 0) {
		rotationState = 3;
	}
}

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffset = 0;
	columnOffset = 0;
}

Block::~Block()
{
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;
	
	for (Position item : tiles) {
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}

	return movedTiles;
}
