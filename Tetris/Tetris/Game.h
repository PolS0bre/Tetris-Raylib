#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	void Render();
	void ManageInput();
	Block GetRandomBlock();
	void MoveBlockDown();
	bool gameOver;
	int score;
	Music music;
private:
	bool IsBlockOutside(), BlockFits();
	void MoveBlockLeft(), MoveBlockRight(), RotateBlock(), LockBlock(), Reset(), UpdateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks;
	Block currentBlock, nextBlock;
	Grid grid;
	Sound rotateSound, lineSound;
};

