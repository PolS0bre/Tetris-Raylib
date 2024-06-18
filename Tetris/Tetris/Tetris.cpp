#include <iostream>
#include "Definiciones.h"
#include "raylib.h"
#include "Game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS");
	SetTargetFPS(60);

	Font font = LoadFontEx("Fonts/monogram.ttf", 64, 0, 0);

	Game game = Game();

	while (!WindowShouldClose()) {
		UpdateMusicStream(game.music);
		//UPDATE PHASSE
		game.ManageInput();
		if (EventTriggered(0.2)) {
			game.MoveBlockDown();
		}

		//RENDER PHASE
		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
		if (game.gameOver) {
			DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
		}
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);
		char scoreText[10];
		sprintf_s(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.2, 6, lightBlue);
		game.Render();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}