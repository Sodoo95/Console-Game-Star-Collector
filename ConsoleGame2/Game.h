#pragma once
#include "State_Manager.h"
#include "State_Menu.h"
class Game
{
private:
	bool isRunning;
public:
	void Start();
	void Run();
	void Update();
	void Render();
	void SetCursorHidden();
};

