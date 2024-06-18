#include "Game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Audio/music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Audio/flip.wav");
	lineSound = LoadSound("Audio/line.wav");
}

Game::~Game()
{
	UnloadSound(lineSound);
	UnloadSound(rotateSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

void Game::Render()
{
	grid.Render();
	currentBlock.Render(11, 11);
	switch (nextBlock.id) {
	case 3:
		nextBlock.Render(255, 290);
		break;
	case 4:
		nextBlock.Render(255, 280);
		break;
	default:
		nextBlock.Render(270, 270);
		break;
	}

}

void Game::ManageInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0) {
		gameOver = false;
		Reset();
	}
	switch (keyPressed) {
		case KEY_LEFT:
			MoveBlockLeft();
			break;
		case KEY_RIGHT:
			MoveBlockRight();
			break;
		case KEY_DOWN:
			MoveBlockDown();
			UpdateScore(0, 1);
			break;
		case KEY_UP:
			RotateBlock();
			break;
		default:
			break;
	}
}

Block Game::GetRandomBlock()
{
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}

	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles) {
		if (grid.IsBlockOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles) {
		if (!grid.IsCellEmpty(item.row, item.column)) {
			return false;
		}
	}

	return true;
}

void Game::MoveBlockLeft()
{
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::RotateBlock()
{
	if (!gameOver) {
		currentBlock.Rotate();
		if (IsBlockOutside() || !BlockFits()) {
			currentBlock.UndoRotate();
		}
		else {
			PlaySound(rotateSound);
		}
	}
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (!BlockFits()) {
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0) {
		PlaySound(lineSound);
		UpdateScore(rowsCleared, 0);
	}
}

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared) {
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}

	score += moveDownPoints;
}
