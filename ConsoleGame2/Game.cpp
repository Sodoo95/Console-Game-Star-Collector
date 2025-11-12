#include "Game.h"

void Game::Start()
{
	isRunning = true;
	SetCursorHidden();
	State_Manager::getInstance().changeState(std::make_unique<State_Menu>());
}

void Game::Run()
{
	while (isRunning)
	{
		Update();
		Render();
	}
}
void Game::Update()
{
	State_Manager::getInstance().update();
}
void Game::Render()
{
	State_Manager::getInstance().render();
}

void Game::SetCursorHidden()
{
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
